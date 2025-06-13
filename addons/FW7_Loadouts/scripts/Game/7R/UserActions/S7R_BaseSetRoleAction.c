[BaseContainerProps(description: "7R Select a premade role Action", configRoot: true)]
class S7R_BaseSetRoleAction : SCR_ScriptedUserAction
{
	protected SCR_PlayerArsenalLoadout m_Loadout;

	//~ Ref
	protected S7R_ResourceHandlerComponent m_ResourceHandler;
	protected SCR_LoadoutManager m_LoadoutManager;
	protected SCR_ArsenalManagerComponent m_ArsenalManager;
	protected SCR_ArsenalComponent m_ArsenalComponent;
	protected RplComponent m_RplComp;
	
	protected bool m_bActionStarted;
	
	//------------------------------------------------------------------------------------------------
	//! Custom function to be overwritten
	protected bool RetrieveLoadout(out SCR_PlayerArsenalLoadout loadout)
	{
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		if (!super.CanBeShownScript(user))
			return false;
		
		//~ Added this here cause in Init it is not found, maybe delayed call?
		m_LoadoutManager = GetGame().GetLoadoutManager();

		if (!m_LoadoutManager)
		{
			return false;
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		if (!super.CanBePerformedScript(user))
			return false;
		
		if (!RetrieveLoadout(m_Loadout))
		{
			m_sCannotPerformReason = "Role not found";
			return false;
		}
		
		return true;
	}
	
 	//------------------------------------------------------------------------------------------------
 	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
 	{
		if (!m_ArsenalManager || !m_RplComp || m_RplComp.IsProxy())
			return;
		
		if(!m_Loadout)
			return;

		// Find player id
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		if (playerId <= 0)
			return;
		
		super.PerformAction(pOwnerEntity, pUserEntity);
		
		// GetPlayerController
		SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		
		if (!playerController)
		{
			Print("[S7R_SetLoadoutAction: PerformAction] playerController not present", LogLevel.ERROR);
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
		super.OnActionStart(pUserEntity);
		
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

		m_ArsenalComponent = SCR_ArsenalComponent.Cast(GetOwner().FindComponent(SCR_ArsenalComponent));
		SCR_ArsenalManagerComponent.GetArsenalManager(m_ArsenalManager);

		if (!m_ArsenalManager || !m_ArsenalComponent)
		{
			Print("[SCR_SetLoadoutAction_7R: Init] No arsenalmanager found", LogLevel.ERROR);
			return;
		}
		
		m_RplComp = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}
}
