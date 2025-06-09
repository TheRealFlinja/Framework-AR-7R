[BaseContainerProps(configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
modded class SCR_PlayerArsenalLoadout : SCR_FactionPlayerLoadout
{	
	[Attribute("Loadout7R")]
	string m_sS7RSlotId;
	
	//------------------------------------------------------------------------------------------------
	string GetSlotID()
	{
		return m_sS7RSlotId;
	}

	//------------------------------------------------------------------------------------------------
	override void OnLoadoutSpawned(GenericEntity pOwner, int playerId)
	{
		if (pOwner)
		{
			FactionAffiliationComponent comp = FactionAffiliationComponent.Cast(pOwner.FindComponent(FactionAffiliationComponent));
			if (comp)
				comp.SetAffiliatedFactionByKey(m_sAffiliatedFaction);
		}
		
		SCR_ArsenalManagerComponent arsenalManager;
		if (!SCR_ArsenalManagerComponent.GetArsenalManager(arsenalManager))
			return;
		
		string playerUID = SCR_ArsenalManagerComponent.S7R_GetPlayerUID(playerId);
		GameEntity playerEntity = GameEntity.Cast(pOwner);
		if (!playerEntity)
			return;
		
		S7R_ArsenalPlayerLoadout playerArsenalLoadout = arsenalManager.S7R_GetPlayerLoadoutData_S(playerId, m_sS7RSlotId);
		if (!playerArsenalLoadout)
			return;
		
		FactionAffiliationComponent factionComponent = FactionAffiliationComponent.Cast(playerEntity.FindComponent(FactionAffiliationComponent));
		if (!factionComponent)
			return;

		if (!playerArsenalLoadout.LoadCharacterFromFile(playerUID, m_sAffiliatedFaction, m_sS7RSlotId, playerEntity))
			arsenalManager.S7R_DeletePlayerArsenalLoadout_S(m_sS7RSlotId, playerId, m_sAffiliatedFaction); // Deserialisation failed, delete saved arsenal loadout
	}
	
	//------------------------------------------------------------------------------------------------
	override bool IsLoadoutAvailableClient()
	{
		SCR_ArsenalManagerComponent arsenalManager;
		return SCR_ArsenalManagerComponent.GetArsenalManager(arsenalManager) && arsenalManager.S7R_IsPlayerArsenalLoadoutValid_C(m_sS7RSlotId);
	}

	//------------------------------------------------------------------------------------------------
	bool S7R_GetLoadoutData_C(out SCR_PlayerLoadoutData data)
	{
		SCR_ArsenalManagerComponent arsenalManager;
		if (!SCR_ArsenalManagerComponent.GetArsenalManager(arsenalManager))
			return false;
		data = arsenalManager.S7R_GetPlayerLoadoutData_C(m_sS7RSlotId);
		return data != null;
	}
}
