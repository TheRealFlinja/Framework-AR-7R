/*

TO DO:

	Test

*/

class SCR_SetLoadoutAction : SCR_BaseFactionCheckUserAction
{	
	[Attribute("", UIWidgets.ComboBox, enumType: ERoles7R, category: "Role selection")]
	protected ERoles7R m_eRole;
	
	//~ Ref
	protected S7R_ResourceHandlerComponent m_ResourceHandler;
	protected SCR_LoadoutManager m_LoadoutManager;
	protected SCR_ArsenalManagerComponent m_ArsenalManager;
	protected SCR_ArsenalComponent m_ArsenalComponent;
	protected RplComponent m_RplComp;
	
	protected bool m_bActionStarted;
	
	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		//~ Added this here cause in Init it is not found, maybe delayed call?
		m_LoadoutManager = GetGame().GetLoadoutManager();

		if (!m_LoadoutManager)
		{
			Print("[SCR_SetLoadoutAction_7R: CanBeShownScript] No loadoutmanager found ", LogLevel.ERROR);
			return false;
		}
		
		if (!m_eRole)
			return false;
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		if (!m_eRole || !m_LoadoutManager || !m_ArsenalManager)
		{
			m_sCannotPerformReason = "Role not available";
			return false;
		}
		
		return true;
	}
	
 	//------------------------------------------------------------------------------------------------
 	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
 	{
		if (!m_ArsenalManager || !m_RplComp || m_RplComp.IsProxy())
			return;
		
		// Find loadout data
		SCR_PlayerArsenalLoadout loadout = m_LoadoutManager.GetLoadoutByRole(m_eRole);
		
		if(!loadout)
		{
			Print(("[SCR_SetLoadoutAction_7R: PerformAction] No loadout found for role " + m_eRole), LogLevel.WARNING);
			return;
		}

		// Find player id
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		if (playerId <= 0)
			return;
		
		// GetPlayerController
		SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		
		if (!playerController)
		{
			Print("[SCR_SetLoadoutAction_7R: PerformAction] playerController not present", LogLevel.ERROR);
			return;
		}
		
		if (!m_OwnerFactionAffiliation)
		{
			Print("[SCR_SetLoadoutAction_7R: PerformAction] No faction found", LogLevel.ERROR);
			return;
		}

		Faction faction = m_OwnerFactionAffiliation.GetAffiliatedFaction();
		FactionKey factionKey;
		if (faction)
			factionKey = faction.GetFactionKey();
		
		if (!factionKey)
		{
			CharacterEntity character = CharacterEntity.Cast(playerController.GetControlledEntity());
			if (!character)
				return;
			factionKey = FactionAffiliationComponent.Cast(character.FindComponent(FactionAffiliationComponent)).GetAffiliatedFactionKey();
			if (!factionKey)
				return;
		}
		
		
		// Get LoadoutEditor Component
		S7R_LoadoutEditorPlayerComponent editorPlayerComponent = S7R_LoadoutEditorPlayerComponent.Cast(playerController.FindComponent(S7R_LoadoutEditorPlayerComponent));
		if (!editorPlayerComponent)
		{
			Print("[SCR_SetLoadoutAction_7R: PerformAction] editorPlayerComponent not present", LogLevel.ERROR);
			return;
		}
		
		// Set as official loadout
		m_ArsenalManager.S7R_TrySetPlayerArsenalLoadout_S("Loadout7R", playerId, loadout, m_ArsenalComponent, SCR_EArsenalSupplyCostType.DEFAULT);
		
		// Load loadout
		m_ArsenalManager.S7R_LoadPlayerArsenalLoadout_S("Loadout7R", playerId, GameEntity.Cast(pUserEntity))
 	}
	
	//------------------------------------------------------------------------------------------------
	override void OnActionStart(IEntity pUserEntity)
	{
		if (!m_eRole)
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
		if (!m_eRole)
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
			Print("[SCR_SetLoadoutAction_7R: Init] No arsenalmanager or arsenalcomponent found ", LogLevel.ERROR);
			return;
		}
		
		m_ResourceHandler = S7R_ResourceHandlerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_ResourceHandlerComponent));
		
		if (!m_ResourceHandler)
		{
			Print("[SCR_SetLoadoutAction_7R: Init] No Resourcehandler found ", LogLevel.ERROR);
			return;
		}
		
		m_RplComp = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}
}
