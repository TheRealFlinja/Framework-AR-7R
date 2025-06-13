/*

TO DO:

	Turn m_Loadout into ResourceName and make as configurable action

*/


[BaseContainerProps(description: "7R Set a premade Loadout Action", configRoot: true)]
class S7R_SetLoadoutAction : SCR_BaseFactionCheckUserAction
{
	protected ref SCR_PlayerArsenalLoadout m_Loadout;

	// protected SCR_LoadoutManager m_LoadoutManager;

	protected SCR_ArsenalManagerComponent m_ArsenalManager;
	protected RplComponent m_RplComp;
	
	protected bool m_bActionStarted;
	
	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		if (!m_ArsenalManager)
		{
			return false;
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		if (!m_Loadout)
		{
			m_sCannotPerformReason = "Loadout not found";
			return false;
		}
		
		return true;
	} 
	
 	//------------------------------------------------------------------------------------------------
 	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
 	{
		if (!m_ArsenalManager || !m_RplComp || m_RplComp.IsProxy())
			return;

		// Find player id
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		if (playerId <= 0)
			return;
		
		// GetPlayerController
		SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		
		if (!playerController)
		{
			Print("[S7R_SetLoadoutAction: PerformAction] playerController not present", LogLevel.ERROR);
			return;
		}
		
		if (!m_OwnerFactionAffiliation)
		{
			Print("[S7R_SetLoadoutAction: PerformAction] No faction found", LogLevel.ERROR);
			return;
		}
		
		// Get LoadoutEditor Component
		S7R_LoadoutEditorPlayerComponent editorPlayerComponent = S7R_LoadoutEditorPlayerComponent.Cast(playerController.FindComponent(S7R_LoadoutEditorPlayerComponent));
		if (!editorPlayerComponent)
		{
			Print("[S7R_SetLoadoutAction: PerformAction] editorPlayerComponent not present", LogLevel.ERROR);
			return;
		}
		
		// Set as saved loadout
		m_ArsenalManager.S7R_TrySetPlayerArsenalLoadout_S("Loadout7R", playerId, m_Loadout, null, SCR_EArsenalSupplyCostType.DEFAULT);
		
		// Load loadout
		m_ArsenalManager.S7R_LoadPlayerArsenalLoadout_S("Loadout7R", playerId, GameEntity.Cast(pUserEntity))
 	}
	
	//------------------------------------------------------------------------------------------------
	override void OnActionStart(IEntity pUserEntity)
	{
		if (!m_Loadout)
			return;
		
		PlayerController playerController = GetGame().GetPlayerController();
		if (!playerController)
			return;
		
		IEntity controlledEntity = playerController.GetControlledEntity();
		if (!controlledEntity)
			return;
		
		if (pUserEntity == controlledEntity)
			m_bActionStarted = true;
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnActionCanceled(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (!m_Loadout)
			return;
		
		PlayerController playerController = GetGame().GetPlayerController();
		if (!playerController)
			return;
		
		IEntity controlledEntity = playerController.GetControlledEntity();
		if (!controlledEntity)
			return;
		
		if (pUserEntity == controlledEntity)
			m_bActionStarted = false;
	}
	
	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		super.Init(pOwnerEntity, pManagerComponent);
		
		if(!GetGame().InPlayMode())
			return;

		SCR_ArsenalManagerComponent.GetArsenalManager(m_ArsenalManager);

		if (!m_ArsenalManager)
		{
			Print("[SCR_SetLoadoutAction_7R: Init] No arsenalmanager found", LogLevel.ERROR);
			return;
		}
		
		m_RplComp = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}
	
	//------------------------------------------------------------------------------------------------
	void CustomInit(SCR_PlayerArsenalLoadout loadout, IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		SCR_ArsenalManagerComponent.GetArsenalManager(m_ArsenalManager);

		if (!m_ArsenalManager)
		{
			Print("[S7R_SetLoadoutAction: CustomInit] Failed configuration", LogLevel.ERROR);
			return;
		}
		
		m_Loadout = loadout;
		m_RplComp = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}
}
