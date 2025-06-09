[EntityEditorProps(category: "Framework7R/Components/Player", description: "player component")]
class S7R_LoadoutEditorPlayerComponentClass : ScriptComponentClass
{}

class S7R_LoadoutEditorPlayerComponent : ScriptComponent
{
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	void S7R_DoDeleteLoadout(string loadoutId, string factionKey, int playerId)
	{
		if (playerId != SCR_PlayerController.GetLocalPlayerId())
			return;
		
		SCR_ArsenalManagerComponent arsenalManager;
		if (SCR_ArsenalManagerComponent.GetArsenalManager(arsenalManager))
			arsenalManager.S7R_DeletePlayerArsenalLoadout_C(factionKey, loadoutId);
	}
	
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	void S7RDo_S7RSaveArsenalLoadout(int playerId, string factionKey, array<ref SCR_PlayerLoadoutData> loadoutsData)
	{
		if (playerId != SCR_PlayerController.GetLocalPlayerId())
			return;

		SCR_ArsenalManagerComponent arsenalManager;
	
		if (!SCR_ArsenalManagerComponent.GetArsenalManager(arsenalManager))
			return;

		map<string, ref SCR_PlayerLoadoutData> playerLoadouts = new map<string, ref SCR_PlayerLoadoutData>();
		arsenalManager.m_mS7RLocalPlayerLoadoutSlots.Set(factionKey, playerLoadouts);
		foreach(SCR_PlayerLoadoutData data : loadoutsData)
		{
			playerLoadouts.Set(data.SlotId, data); 
		}
	}
	
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	void S7R_DoSendPlayerLoadout(int playerId, string factionKey, SCR_PlayerLoadoutData loadoutData)
	{
		if (playerId != SCR_PlayerController.GetLocalPlayerId())
			return;
		
		SCR_ArsenalManagerComponent arsenalManager;
		if (!SCR_ArsenalManagerComponent.GetArsenalManager(arsenalManager))
			return;
		
		arsenalManager.m_LocalPlayerLoadoutData = loadoutData;
		if (!arsenalManager.m_mS7RLocalPlayerLoadoutSlots.Get(factionKey))
			arsenalManager.m_mS7RLocalPlayerLoadoutSlots.Set(factionKey, new map<string, ref SCR_PlayerLoadoutData>());
		
		arsenalManager.m_mS7RLocalPlayerLoadoutSlots.Get(factionKey).Set(loadoutData.SlotId, loadoutData);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	void S7R_DoSetPlayerHasLoadout(int playerId, bool loadoutValid, bool loadoutChanged, bool notification)
	{
		if (playerId != SCR_PlayerController.GetLocalPlayerId())
			return;
		
		SCR_ArsenalManagerComponent arsenalManager;
		if (SCR_ArsenalManagerComponent.GetArsenalManager(arsenalManager))
			arsenalManager.S7R_SetPlayerHasLoadout(loadoutValid, loadoutChanged, notification);
	}
}