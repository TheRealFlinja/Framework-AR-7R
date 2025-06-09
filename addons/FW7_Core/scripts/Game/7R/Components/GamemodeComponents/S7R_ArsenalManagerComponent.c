modded class SCR_ArsenalManagerComponent : SCR_BaseGameModeComponent
{
	// Map of <Player, <SlotID, LoadoutData>>
	ref map<string, ref map<string, ref SCR_PlayerLoadoutData>> m_mS7RLocalPlayerLoadoutSlots = new map<string, ref map<string, ref SCR_PlayerLoadoutData>>();
	protected ref map<string, ref map<string, ref map<string, ref S7R_ArsenalPlayerLoadout>>> m_mS7RPlayerLoadoutSlots = new map<string, ref map<string, ref map<string, ref S7R_ArsenalPlayerLoadout>>>();
	protected ref map<string, ref S7R_ArsenalPlayerLoadout> m_mS7RSelectedPlayerLoadoutSlots = new map<string, ref S7R_ArsenalPlayerLoadout>();
	
	//------------------------------------------------------------------------------------------------
	SCR_PlayerLoadoutData S7R_GetPlayerLoadoutData_C(string slotId)
	{
		Faction faction = SCR_FactionManager.SGetLocalPlayerFaction();
		if (!faction)
			return null;
		
		map<string, ref SCR_PlayerLoadoutData> loadouts = m_mS7RLocalPlayerLoadoutSlots[faction.GetFactionKey()];
		if (!loadouts)
			return null;

		return loadouts[slotId];
	}

	//------------------------------------------------------------------------------------------------
	map<string, ref SCR_PlayerLoadoutData> S7R_GetPlayerLoadouts_C()
	{
		Faction faction = SCR_FactionManager.SGetLocalPlayerFaction();
		if (!faction)
			return null;
		
		map<string, ref SCR_PlayerLoadoutData> loadouts = m_mS7RLocalPlayerLoadoutSlots[faction.GetFactionKey()];
		return loadouts;
	}

	//------------------------------------------------------------------------------------------------
	S7R_ArsenalPlayerLoadout S7R_GetPlayerLoadoutData_S(int playerId, string slotId)
	{
		const string playerUID = S7R_GetPlayerUID(playerId);
		map<string, ref map<string, ref S7R_ArsenalPlayerLoadout>> loadoutsByFaction = m_mS7RPlayerLoadoutSlots[playerUID];
		if (!loadoutsByFaction)
			return null;

		map<string, ref S7R_ArsenalPlayerLoadout> loadouts = loadoutsByFaction[SCR_FactionManager.SGetPlayerFaction(playerId).GetFactionKey()];
		if (!loadouts)
			return null;

		return loadouts[slotId];
	}

	//------------------------------------------------------------------------------------------------
	map<string, ref S7R_ArsenalPlayerLoadout> S7R_GetPlayerLoadouts_S(int playerId, string factionKey)
	{
		const string playerUID = S7R_GetPlayerUID(playerId);
		map<string, ref map<string, ref S7R_ArsenalPlayerLoadout>> playerLoadoutsByFaction = m_mS7RPlayerLoadoutSlots.Get(playerUID);
		if (!playerLoadoutsByFaction)
			return null;

		map<string, ref S7R_ArsenalPlayerLoadout> playerLoadouts = playerLoadoutsByFaction.Get(factionKey);
		return playerLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	void S7R_SetPlayerLoadouts_S(int playerId, string factionKey, map<string, ref S7R_ArsenalPlayerLoadout> loadouts)
	{
		const string playerUID = S7R_GetPlayerUID(playerId);
		map<string, ref map<string, ref S7R_ArsenalPlayerLoadout>> playerLoadoutsByFaction = m_mS7RPlayerLoadoutSlots.Get(playerUID);
		if (!playerLoadoutsByFaction)
		{
			playerLoadoutsByFaction = new map<string, ref map<string, ref S7R_ArsenalPlayerLoadout>>();
			m_mS7RPlayerLoadoutSlots.Set(playerUID, playerLoadoutsByFaction);
		}

		playerLoadoutsByFaction.Set(factionKey, loadouts);
	}

	//------------------------------------------------------------------------------------------------
	S7R_ArsenalPlayerLoadout S7R_GetSelectedPlayerLoadoutData_S(string playerId)
	{
		return m_mS7RSelectedPlayerLoadoutSlots[playerId];
	}

	//------------------------------------------------------------------------------------------------
	override void SetLoadoutBlackListActiveStates(notnull array<bool> orderedActiveStates, bool clearExistingLoadouts, int editorPlayerIdClearedLoadout = -1)
	{
		if (!m_LoadoutSaveBlackListHolder || !GetGameMode().IsMaster())
			return;
		
		if (editorPlayerIdClearedLoadout > 0)
			SCR_NotificationsComponent.SendToEveryone(ENotification.EDITOR_CHANGED_LOADOUT_SAVE_BLACKLIST, editorPlayerIdClearedLoadout);
		
		m_LoadoutSaveBlackListHolder.SetOrderedBlackListsActive(orderedActiveStates);
		
		//~ Clear existing loadouts
		if (clearExistingLoadouts)
		{
			//~ Clear local loadout
			Rpc(RPC_OnPlayerLoadoutCleared, editorPlayerIdClearedLoadout);
			RPC_OnPlayerLoadoutCleared(editorPlayerIdClearedLoadout);
			
			//~ Clear existing loadouts on server
			m_mS7RPlayerLoadoutSlots.Clear();
			m_mS7RSelectedPlayerLoadoutSlots.Clear();
		}
	}
	
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	override protected void RPC_OnPlayerLoadoutCleared(int playerIdClearedLoadout)
	{
		if (!m_bLocalPlayerLoadoutAvailable)
			return;
		
		//~ No local loadout available anymore
		m_bLocalPlayerLoadoutAvailable = false;
		m_mS7RLocalPlayerLoadoutSlots.Clear();
		
		//~ Player loadout was cleared. This can happen when respawn menu is open and needs to be refreshed
		m_OnPlayerLoadoutUpdated.Invoke(SCR_PlayerController.GetLocalPlayerId(), false);
		
		//~ Send notification to player to inform them their loadout was cleared
		if (playerIdClearedLoadout > 0)
			SCR_NotificationsComponent.SendLocal(ENotification.PLAYER_LOADOUT_CLEARED_BY_EDITOR);
		else 
			SCR_NotificationsComponent.SendLocal(ENotification.PLAYER_LOADOUT_CLEARED);
	}

	//------------------------------------------------------------------------------------------------
	bool S7R_IsPlayerArsenalLoadoutValid_C(string slotId)
	{
		Faction faction = SCR_FactionManager.SGetLocalPlayerFaction();
		if (!faction)
			return false;

		map<string, ref SCR_PlayerLoadoutData> loadouts = m_mS7RLocalPlayerLoadoutSlots.Get(faction.GetFactionKey());
		if (!loadouts)
			return false;

		return loadouts.Contains(slotId);
	}

	//------------------------------------------------------------------------------------------------
	void S7R_DeletePlayerArsenalLoadout_S(string loadoutID, int playerId, string factionKey)
	{
		map<string, ref S7R_ArsenalPlayerLoadout> playerLoadouts = S7R_GetPlayerLoadouts_S(playerId, factionKey);
		if (!playerLoadouts)
			return;

		S7R_ArsenalPlayerLoadout loadout;
		if (!playerLoadouts.Take(loadoutID, loadout))
			return;

		loadout.DeleteFile();

		const PlayerController playerController = GetGame().GetPlayerManager().GetPlayerController(playerId);
		const S7R_LoadoutEditorPlayerComponent editorPlayerComponent = S7R_LoadoutEditorPlayerComponent.Cast(playerController.FindComponent(S7R_LoadoutEditorPlayerComponent));
		if (editorPlayerComponent)
			editorPlayerComponent.Rpc(editorPlayerComponent.S7R_DoDeleteLoadout, loadoutID, factionKey, playerId);
	}

	//------------------------------------------------------------------------------------------------
	void S7R_DeletePlayerArsenalLoadout_C(string faction, string loadoutID)
	{
		map<string, ref SCR_PlayerLoadoutData> loadouts = m_mS7RLocalPlayerLoadoutSlots[faction];
		if (!loadouts)
			return;

		loadouts.Remove(loadoutID);
	}

	//------------------------------------------------------------------------------------------------
	void S7R_TrySavePlayerArsenalLoadout_S(
		string slotId,
		int playerId,
		notnull GameEntity characterEntity,
		SCR_ArsenalComponent arsenalComponent,
		SCR_EArsenalSupplyCostType arsenalSupplyType
	)
	{
		if (!GetGameMode().IsMaster())
			return;

		const SCR_PlayerController clientPlayerController = SCR_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		if (!clientPlayerController || clientPlayerController.IsPossessing())
			return;

		const FactionAffiliationComponent factionAffiliation = FactionAffiliationComponent.Cast(characterEntity.FindComponent(FactionAffiliationComponent));
		if (!factionAffiliation)
			return;
		
		string factionKey = factionAffiliation.GetAffiliatedFaction().GetFactionKey();
		if (factionKey.IsEmpty() || factionKey == SCR_PlayerArsenalLoadout.ARSENALLOADOUT_FACTIONKEY_NONE)
			return;

		if (!CanSaveLoadout(playerId, characterEntity, factionAffiliation, arsenalComponent, true))
			return;

		S7R_SavePlayerArsenalLoadout_S(slotId, factionKey, playerId, characterEntity, arsenalSupplyType);
	}

	//------------------------------------------------------------------------------------------------
	private void S7R_SavePlayerArsenalLoadout_S(string slotId, string factionKey, int playerId, notnull GameEntity characterEntity, SCR_EArsenalSupplyCostType arsenalSupplyType)
	{
		const string playerUID = S7R_GetPlayerUID(playerId);
		const S7R_ArsenalPlayerLoadout currentLoadout = m_mS7RSelectedPlayerLoadoutSlots.Get(playerUID);
		const string characterSaveJson = S7R_ArsenalPlayerLoadout.GetCharacterSaveJson(characterEntity);
		const int newLoadoutHash = characterSaveJson.Hash();
		const bool isLoadoutValid = newLoadoutHash != 0;
		const bool didLoadoutChange = isLoadoutValid && (!currentLoadout || (newLoadoutHash != currentLoadout.Hash || slotId != currentLoadout.SlotId));

		if (didLoadoutChange)
		{
			map<string, ref S7R_ArsenalPlayerLoadout> playerLoadouts = S7R_GetPlayerLoadouts_S(playerId, factionKey);
			if (!playerLoadouts)
			{
				playerLoadouts = new map<string, ref S7R_ArsenalPlayerLoadout>();
				S7R_SetPlayerLoadouts_S(playerId, factionKey, playerLoadouts);
			}

			// Create new loadout
			S7R_ArsenalPlayerLoadout newLoadout();
			m_mS7RSelectedPlayerLoadoutSlots.Set(playerUID, newLoadout);
			playerLoadouts.Set(slotId, newLoadout);

			// Create temp loadout for cost calulation (uses exiting vanilla code for calculations)
			SCR_ArsenalPlayerLoadout tempLoadoutForCostCalculation();
			tempLoadoutForCostCalculation.loadout = characterSaveJson;

			const FactionAffiliationComponent factionAffiliation = FactionAffiliationComponent.Cast(characterEntity.FindComponent(FactionAffiliationComponent));
			ComputeSuppliesCost(SCR_Faction.Cast(factionAffiliation.GetAffiliatedFaction()), tempLoadoutForCostCalculation, arsenalSupplyType);

			newLoadout.Hash = newLoadoutHash;
			newLoadout.SlotId = slotId;
			newLoadout.PlayerUID = playerUID;
			newLoadout.FactionK = factionKey;
			newLoadout.Loadout = GetPlayerLoadoutData(characterEntity);
			newLoadout.LoadoutCost = 0;
			newLoadout.Loadout.LoadoutCost = 0;
			newLoadout.Loadout.FactionIndex = GetGame().GetFactionManager().GetFactionIndex(SCR_FactionManager.SGetPlayerFaction(playerId));
			newLoadout.Loadout.SlotId = slotId;
			newLoadout.SaveLoadoutToFile(characterEntity);

			const PlayerController playerController = GetGame().GetPlayerManager().GetPlayerController(playerId);
			const S7R_LoadoutEditorPlayerComponent editorPlayerComponent = S7R_LoadoutEditorPlayerComponent.Cast(playerController.FindComponent(S7R_LoadoutEditorPlayerComponent));
			if (editorPlayerComponent)
				editorPlayerComponent.Rpc(editorPlayerComponent.S7R_DoSendPlayerLoadout, playerId, factionKey, newLoadout.Loadout);
		}

		Rpc(DoSetPlayerHasLoadout, playerId, isLoadoutValid, didLoadoutChange, true);
	}

	//------------------------------------------------------------------------------------------------
	//! Authority side
	void S7R_LoadPlayerArsenalLoadout_S(string slotId, int playerId, GameEntity characterEntity)
	{
		if (!characterEntity)
			return;

		const SCR_PlayerController clientPlayerController = SCR_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		if (!clientPlayerController || clientPlayerController.IsPossessing())
			return;

		const S7R_LoadoutEditorPlayerComponent editorPlayerComponent = S7R_LoadoutEditorPlayerComponent.Cast(clientPlayerController.FindComponent(S7R_LoadoutEditorPlayerComponent));
		if (!editorPlayerComponent)
			return;

		S7R_ArsenalPlayerLoadout playerLoadout = S7R_GetPlayerLoadoutData_S(playerId, slotId);
		if (!playerLoadout)
			return;

		const string playerUID = S7R_GetPlayerUID(playerId);
		const string factionKey = SCR_FactionManager.SGetPlayerFaction(playerId).GetFactionKey();
		if (!playerLoadout.LoadCharacterFromFile(playerUID, factionKey, slotId, characterEntity))
			return;

		m_mS7RSelectedPlayerLoadoutSlots.Set(playerUID, playerLoadout);
		
		editorPlayerComponent.Rpc(editorPlayerComponent.S7R_DoSendPlayerLoadout, playerId, factionKey, playerLoadout.Loadout);
		editorPlayerComponent.Rpc(editorPlayerComponent.S7R_DoSetPlayerHasLoadout, playerId, true, true, false);
	}
	
	//------------------------------------------------------------------------------------------------
	void S7R_TrySetPlayerArsenalLoadout_S(
		string slotId,
		int playerId,
		notnull SCR_PlayerArsenalLoadout playerLoadout,
		SCR_ArsenalComponent arsenalComponent,
		SCR_EArsenalSupplyCostType arsenalSupplyType
	)
	{
		if (!GetGameMode().IsMaster())
			return;

		const SCR_PlayerController clientPlayerController = SCR_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		if (!clientPlayerController || clientPlayerController.IsPossessing())
			return;
		
		// Spawn CharacterEntity Locally to retrieve loadout information
		ResourceName loadoutResource = playerLoadout.GetLoadoutResource();
		if (!loadoutResource)
			return;
				
		Resource resource = Resource.Load(loadoutResource);
		if (!resource)
			return;
		
		IEntity ent = GetGame().SpawnEntityPrefabLocal(resource);
		if (!ent)
			return;
		
		GameEntity characterEntity = GameEntity.Cast(ent);
		if (!characterEntity)
			return;

		const FactionAffiliationComponent factionAffiliation = FactionAffiliationComponent.Cast(clientPlayerController.FindComponent(FactionAffiliationComponent));
		if (!factionAffiliation)
			return;
		
		string factionKey = factionAffiliation.GetAffiliatedFaction().GetFactionKey();
		if (factionKey.IsEmpty() || factionKey == SCR_PlayerArsenalLoadout.ARSENALLOADOUT_FACTIONKEY_NONE)
			return;

		if (!CanSaveLoadout(playerId, characterEntity, factionAffiliation, arsenalComponent, true))
			return;

		S7R_SavePlayerArsenalLoadout_S(slotId, factionKey, playerId, characterEntity, arsenalSupplyType);
	}

	//------------------------------------------------------------------------------------------------
	override bool GetLocalPlayerLoadoutAvailable()
	{
		if (m_mS7RLocalPlayerLoadoutSlots.IsEmpty())
			return false;

		const Faction faction = SCR_FactionManager.SGetLocalPlayerFaction();
		if (!faction)
			return false;

		map<string, ref SCR_PlayerLoadoutData> loadouts = m_mS7RLocalPlayerLoadoutSlots.Get(SCR_FactionManager.SGetLocalPlayerFaction().GetFactionKey());
		if (!loadouts)
			return false;

		foreach(string key, SCR_PlayerLoadoutData value : loadouts)
		{
			if (value.FactionIndex == GetGame().GetFactionManager().GetFactionIndex(faction))
				return true;
		}
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	override protected void OnPlayerConnected(int playerId)
	{
		super.OnPlayerConnected(playerId);
		if (RplSession.Mode() == RplMode.Dedicated)
			return;
		
		S7R_InitPlayerLoadouts(playerId);
	}
	//------------------------------------------------------------------------------------------------
	override protected void OnPlayerAuditSuccess(int playerId)
	{
		m_aPlayerLoadouts.Clear();
		super.OnPlayerAuditSuccess(playerId);
		S7R_InitPlayerLoadouts(playerId);
	}

	//------------------------------------------------------------------------------------------------
	protected void S7R_InitPlayerLoadouts(int playerId)
	{
		// Get PlayerController
		const PlayerController playerController = GetGame().GetPlayerManager().GetPlayerController(playerId);
		if (!playerController)
			return;
		
		// Get LoadoutEditorComponent
		const S7R_LoadoutEditorPlayerComponent editorPlayerComponent = S7R_LoadoutEditorPlayerComponent.Cast(playerController.FindComponent(S7R_LoadoutEditorPlayerComponent));
		if (!editorPlayerComponent)
			return;
		
		const string playerUID = S7R_GetPlayerUID(playerId);
		if (!playerUID)
			return;

		// Create new mapping
		m_mS7RPlayerLoadoutSlots.Set(playerUID, new map<string, ref map<string, ref S7R_ArsenalPlayerLoadout>>());
		auto playerLoadoutsByFaction = m_mS7RPlayerLoadoutSlots.Get(playerUID);

		// Load previous loadouts for faction (for reconnects)
		// See if this carries over between missions persistent
		const map<string, ref array<ref SCR_PlayerLoadoutData>> playerLoadoutsDataByFaction = new map<string, ref array<ref SCR_PlayerLoadoutData>>();
		const array<ref S7R_ArsenalPlayerLoadout> loadouts = S7R_ArsenalPlayerLoadout.LoadAllFromFolder(playerUID);
		foreach(S7R_ArsenalPlayerLoadout loadout : loadouts)
		{
			if (!playerLoadoutsByFaction.Get(loadout.FactionK))
				playerLoadoutsByFaction.Set(loadout.FactionK, new map<string, ref S7R_ArsenalPlayerLoadout>()); 
		
			playerLoadoutsByFaction.Get(loadout.FactionK).Set(loadout.SlotId, loadout);
		
			if (!playerLoadoutsDataByFaction.Get(loadout.FactionK))
				playerLoadoutsDataByFaction.Set(loadout.FactionK, {}); 
		
			playerLoadoutsDataByFaction.Get(loadout.FactionK).Insert(loadout.Loadout);	
		}
		
		foreach(string faction, array<ref SCR_PlayerLoadoutData> data : playerLoadoutsDataByFaction)
		{
			editorPlayerComponent.Rpc(editorPlayerComponent.S7RDo_S7RSaveArsenalLoadout, playerId, faction, data);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override static float GetLoadoutCalculatedSupplyCost(notnull SCR_BasePlayerLoadout playerLoadout, bool getLocalPlayer, int playerID, SCR_Faction playerFaction, IEntity spawnTarget, out SCR_CampaignMilitaryBaseComponent spawnPointParentBase = null, out SCR_ResourceComponent spawnpointResourceComponent = null)
	{		
		return 0;
	}

	//------------------------------------------------------------------------------------------------
	void S7R_SetPlayerHasLoadout(bool loadoutValid, bool loadoutChanged, bool notification)
	{
		if (notification)
		{
			if (m_bLocalPlayerLoadoutAvailable != loadoutValid || loadoutChanged)
			{
				//~ Send notification with loadout cost
				if (m_LocalPlayerLoadoutData && GetCalculatedLoadoutSpawnSupplyCostMultiplier() > 0)
					SCR_NotificationsComponent.SendLocal(ENotification.PLAYER_LOADOUT_SAVED_SUPPLY_COST, m_LocalPlayerLoadoutData.LoadoutCost);
				//~ Set notification without loadout cost
				else
					SCR_NotificationsComponent.SendLocal(ENotification.PLAYER_LOADOUT_SAVED);
			}
			else
			{
				SCR_NotificationsComponent.SendLocal(ENotification.PLAYER_LOADOUT_NOT_SAVED_UNCHANGED);
			}
		}

		m_bLocalPlayerLoadoutAvailable = loadoutValid;
		m_OnPlayerLoadoutUpdated.Invoke(SCR_PlayerController.GetLocalPlayerId(), loadoutValid);
	}

	//------------------------------------------------------------------------------------------------
	static string S7R_GetPlayerUID(int playerId)
	{
		if (!Replication.IsServer())
			return GetGame().GetBackendApi().GetLocalIdentityId();

		string uid = GetGame().GetBackendApi().GetPlayerIdentityId(playerId);
		if (!uid)
		{
			if (RplSession.Mode() != RplMode.Dedicated)
				uid = string.Format("bbbbdddd-0000-0000-0000-%1", playerId.ToString(12));
		}

		return uid;
	}
}


class S7R_ArsenalPlayerLoadout : Managed
{
	static const string LOADOUTS_FOLDER_PATH = "S7R_LoadoutEditor/loadouts";
	
	[NonSerialized()]
	ref SCR_PlayerLoadoutData Loadout;
	int LoadoutCost;
	int Hash;
	string FactionK;
	string SlotId;
	string PlayerUID;
	
	
	//------------------------------------------------------------------------------------------------
	void SaveLoadoutToFile(GameEntity characterEntity)
	{
		const string loadoutId = S7R_LoadoutEditorServerConfig.GetInstance().LoadoutId;
		if (!FileIO.FileExists(string.Format("$profile:%1/%2/%3", LOADOUTS_FOLDER_PATH, PlayerUID, loadoutId)))
		{
			if (!FileIO.MakeDirectory(string.Format("$profile:%1/%2/%3", LOADOUTS_FOLDER_PATH, PlayerUID, loadoutId)))
				return;
		}

		const SCR_BinSaveContext saveContext = new SCR_BinSaveContext();
		saveContext.WriteValue("loadoutClothings", Loadout.Clothings);
		saveContext.WriteValue("loadoutWeapons", Loadout.Weapons);
		saveContext.WriteValue("loadoutLoadoutCost", Loadout.LoadoutCost);
		saveContext.WriteValue("loadoutFactionIndex", Loadout.FactionIndex);
		saveContext.WriteValue("LoadoutCost", LoadoutCost);
		saveContext.WriteValue("Hash", Hash);
		saveContext.WriteValue("FactionK", FactionK);
		saveContext.WriteValue("SlotId", SlotId);
		saveContext.WriteValue("PlayerUID", PlayerUID);
		saveContext.SaveToFile(string.Format("$profile:%1/%2/%3/%4-%5.bin", LOADOUTS_FOLDER_PATH, PlayerUID, loadoutId, FactionK, SlotId));

		SaveCharacterToFile(PlayerUID, FactionK, SlotId, characterEntity);
	}
	
	//------------------------------------------------------------------------------------------------
	static array<ref S7R_ArsenalPlayerLoadout> LoadAllFromFolder(string playerUID)
	{
		const string loadoutId = S7R_LoadoutEditorServerConfig.GetInstance().LoadoutId;
		const string loadoutFilePath = string.Format("$profile:%1/%2/%3/", LOADOUTS_FOLDER_PATH, playerUID, loadoutId);
		array<string> files = {};
		FileIO.FindFiles(files.Insert, loadoutFilePath, ".bin");
		
		array<ref S7R_ArsenalPlayerLoadout> loadouts = {};
		loadouts.Reserve(files.Count());
		S7R_ArsenalPlayerLoadout loadout;
		foreach(string file : files)
		{
			if (file.Contains("/characters/"))
				continue;
			
			loadout = LoadLoadoutFromFile(file);
			if (loadout)
				loadouts.Insert(loadout);
		}
		return loadouts;
	}

	//------------------------------------------------------------------------------------------------
	static S7R_ArsenalPlayerLoadout LoadLoadoutFromFile(string file)
	{
		const SCR_BinLoadContext loadContext = new SCR_BinLoadContext();
		loadContext.LoadFromFile(file);
		SCR_PlayerLoadoutData loadout();
		loadContext.ReadValue("loadoutClothings", loadout.Clothings);
		loadContext.ReadValue("loadoutWeapons", loadout.Weapons);
		loadContext.ReadValue("loadoutLoadoutCost", loadout.LoadoutCost);
		loadContext.ReadValue("loadoutFactionIndex", loadout.FactionIndex);
		S7R_ArsenalPlayerLoadout arsenalLoadout();
		loadContext.ReadValue("LoadoutCost", arsenalLoadout.LoadoutCost);
		loadContext.ReadValue("Hash", arsenalLoadout.Hash);
		loadContext.ReadValue("FactionK", arsenalLoadout.FactionK);
		loadContext.ReadValue("SlotId", arsenalLoadout.SlotId);
		loadContext.ReadValue("PlayerUID", arsenalLoadout.PlayerUID);
		loadout.SlotId = arsenalLoadout.SlotId;
		arsenalLoadout.Loadout = loadout;
		if (!arsenalLoadout)
			return null;

		return arsenalLoadout;
	}

	//------------------------------------------------------------------------------------------------
	void DeleteFile()
	{
		const string loadoutId = S7R_LoadoutEditorServerConfig.GetInstance().LoadoutId;
		FileIO.DeleteFile(string.Format("$profile:%1/%2/%3/%4-%5.bin", LOADOUTS_FOLDER_PATH, PlayerUID, loadoutId, FactionK, SlotId));
		FileIO.DeleteFile(string.Format("$profile:%1/%2/%3/characters/%4-%5.bin", LOADOUTS_FOLDER_PATH, PlayerUID, loadoutId, FactionK, SlotId));
	}

	//------------------------------------------------------------------------------------------------
	private void SaveCharacterToFile(string playerUID, string factionKey, string slotId, GameEntity characterEntity)
	{
		const string loadoutId = S7R_LoadoutEditorServerConfig.GetInstance().LoadoutId;
		if (!FileIO.FileExists(string.Format("$profile:%1/%2/%3/characters", LOADOUTS_FOLDER_PATH, playerUID, loadoutId)))
		{
			if (!FileIO.MakeDirectory(string.Format("$profile:%1/%2/%3/characters", LOADOUTS_FOLDER_PATH, playerUID, loadoutId)))
				return;
		}
		
		const SCR_BinSaveContext saveContext = new SCR_BinSaveContext();
		if (saveContext.WriteValue(SCR_PlayerArsenalLoadout.ARSENALLOADOUT_KEY, characterEntity))
			saveContext.SaveToFile(string.Format("$profile:%1/%2/%3/characters/%4-%5.bin", LOADOUTS_FOLDER_PATH, playerUID, loadoutId, factionKey, slotId));
	}

	//------------------------------------------------------------------------------------------------
	bool LoadCharacterFromFile(string playerUID, string factionKey, string slotId, GameEntity characterEntity)
	{
		const string loadoutId = S7R_LoadoutEditorServerConfig.GetInstance().LoadoutId;
		const string characterFilePath = string.Format("$profile:%1/%2/%3/characters/%4-%5.bin", LOADOUTS_FOLDER_PATH, playerUID, loadoutId, factionKey, slotId);
		if (!FileIO.FileExists(characterFilePath))
			return false;

		const SCR_BinLoadContext loadContext = new SCR_BinLoadContext();
		bool loadSuccess = true;
		loadSuccess &= loadContext.LoadFromFile(characterFilePath);
		loadSuccess &= loadContext.ReadValue(SCR_PlayerArsenalLoadout.ARSENALLOADOUT_KEY, characterEntity);

		return loadSuccess;
	}

	//------------------------------------------------------------------------------------------------
	static string GetCharacterSaveJson(GameEntity playerEntity)
	{
		const SCR_JsonSaveContext saveContext = new SCR_JsonSaveContext();
		saveContext.WriteValue(SCR_PlayerArsenalLoadout.ARSENALLOADOUT_KEY, playerEntity);
		return saveContext.ExportToString();
	}
}

modded class SCR_PlayerLoadoutData
{
	string SlotId;

	
	//------------------------------------------------------------------------------------------------
    override static bool Extract(SCR_PlayerLoadoutData instance, ScriptCtx ctx, SSnapSerializerBase snapshot)
    {
        // Fill a snapshot with values from an instance.
		
		int clothingCount = instance.Clothings.Count();
		snapshot.SerializeInt(clothingCount);
		
		for (int i = 0; i < clothingCount; ++i)
		{
			snapshot.SerializeInt(instance.Clothings[i].SlotIdx);
			
			string resourceName = instance.Clothings[i].ClothingPrefab;
			snapshot.SerializeString(resourceName);
		}
		
		int weaponCount = instance.Weapons.Count();
		snapshot.SerializeInt(weaponCount);
		
		for (int i = 0; i < weaponCount; ++i)
		{
			snapshot.SerializeInt(instance.Weapons[i].SlotIdx);
			
			string resourceName = instance.Weapons[i].WeaponPrefab;
			snapshot.SerializeString(resourceName);
		}

		snapshot.SerializeFloat(instance.LoadoutCost);
		snapshot.SerializeInt(instance.FactionIndex);
		snapshot.SerializeString(instance.SlotId);

        return true;
    }
 
	//------------------------------------------------------------------------------------------------
     override static bool Inject(SSnapSerializerBase snapshot, ScriptCtx ctx, SCR_PlayerLoadoutData instance)
    {
       	 // Fill an instance with values from snapshot.
		int clothingCount;
		snapshot.SerializeInt(clothingCount);
		instance.Clothings.Clear();
		
		for (int i = 0; i < clothingCount; ++i)
		{
			SCR_ClothingLoadoutData clothingData();
			
			snapshot.SerializeInt(clothingData.SlotIdx);
			
			string resourceName;
			snapshot.SerializeString(resourceName);
			clothingData.ClothingPrefab = resourceName;
			
			instance.Clothings.Insert(clothingData);
		}
		
		int weaponCount;
		snapshot.SerializeInt(weaponCount);
		instance.Weapons.Clear();
		
		for (int i = 0; i < weaponCount; ++i)
		{
			SCR_WeaponLoadoutData weaponData();
			
			snapshot.SerializeInt(weaponData.SlotIdx);
			
			string resourceName;
			snapshot.SerializeString(resourceName);
			weaponData.WeaponPrefab = resourceName;
			
			instance.Weapons.Insert(weaponData);
		}

		snapshot.SerializeFloat(instance.LoadoutCost);
		snapshot.SerializeInt(instance.FactionIndex);
		snapshot.SerializeString(instance.SlotId);
		
        return true;
    }
 
	//------------------------------------------------------------------------------------------------
     override static void Encode(SSnapSerializerBase snapshot, ScriptCtx ctx, ScriptBitSerializer packet)
    {
		int clothingCount;
		snapshot.SerializeBytes(clothingCount, 4);
		packet.Serialize(clothingCount, 32);
		
		for (int i = 0; i < clothingCount; ++i)
		{
			snapshot.EncodeInt(packet);
			snapshot.EncodeString(packet);
		}
		
		int weaponCount;
		snapshot.SerializeBytes(weaponCount, 4);
		packet.Serialize(weaponCount, 32);
		
		for (int i = 0; i < weaponCount; ++i)
		{
			snapshot.EncodeInt(packet);
			snapshot.EncodeString(packet);
		}

		snapshot.EncodeFloat(packet);
		snapshot.EncodeInt(packet);
		snapshot.EncodeString(packet);
    }
 
	//------------------------------------------------------------------------------------------------
    override  static bool Decode(ScriptBitSerializer packet, ScriptCtx ctx, SSnapSerializerBase snapshot)
    {
		int clothingCount;
		packet.Serialize(clothingCount, 32);
		snapshot.SerializeBytes(clothingCount, 4);
		
		for (int i = 0; i < clothingCount; ++i)
		{
			snapshot.DecodeInt(packet);
			snapshot.DecodeString(packet);
		}
		
		int weaponCount;
		packet.Serialize(weaponCount, 32);
		snapshot.SerializeBytes(weaponCount, 4);
		
		for (int i = 0; i < weaponCount; ++i)
		{
			snapshot.DecodeInt(packet);
			snapshot.DecodeString(packet);
		}
		
		snapshot.DecodeFloat(packet);
		snapshot.DecodeInt(packet);
		snapshot.DecodeString(packet);
        return true;
    }
}

class S7R_LoadoutEditorServerConfig : Managed
{
	string LoadoutId;
	
	private static ref S7R_LoadoutEditorServerConfig instance;
	
	//------------------------------------------------------------------------------------------------
	static S7R_LoadoutEditorServerConfig GetInstance()
	{
		if (!instance)
		{
			instance = new S7R_LoadoutEditorServerConfig();
			const SCR_MissionHeader missionHeader = SCR_MissionHeader.Cast(GetGame().GetMissionHeader());
			if (missionHeader && missionHeader.m_S7R_LoadoutEditorSettings)
				instance.LoadoutId = missionHeader.m_S7R_LoadoutEditorSettings.m_iLoadoutId;
			else
				instance.LoadoutId = "default";
		}
			
		return instance;
	}
}