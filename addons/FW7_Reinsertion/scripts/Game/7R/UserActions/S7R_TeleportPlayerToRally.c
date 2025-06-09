/*

TO DO:
	- Add an area check for hostiles

*/
[BaseContainerProps(description: "7R Reinsertion method: Teleport to Rally Action", configRoot: true)]
class S7R_TeleportPlayerToRally : SCR_ScriptedUserAction
{	
	// Rally Information
	protected IEntity m_RallyEntity;
	
	protected S7R_ReinsertionManagerComponent m_ReinsertionManager;
	protected RplComponent m_RplComp;
	protected bool m_bActionStarted;

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		if (!m_ReinsertionManager)
		{
			return false;
		}
		
		if (!m_ReinsertionManager.GetRally(m_RallyEntity))
		{
			return false;
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
 	{
		// Find player elements
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		if (playerId <= 0)
			return;

		SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		if (!playerController)
			return;
		
		SCR_FastTravelComponent fastTravelCmp = SCR_FastTravelComponent.Cast(playerController.FindComponent(SCR_FastTravelComponent));
		if (!fastTravelCmp)
		{
			Print("[S7R_TeleportPlayerToRally: PerformAction] fastTravelCmp not found", LogLevel.ERROR);
			return;
		}
		
		RplId rplId = fastTravelCmp.FindDestinationId(m_RallyEntity);
		
		if (!rplId.IsValid())
		{
			Print("[S7R_TeleportPlayerToRally: PerformAction] Invalid rplID", LogLevel.ERROR);
			return;
		}
		
		fastTravelCmp.SetDestination(rplId, "Rally");
		
		if (fastTravelCmp.GetDestinationName() != "Rally")
		{
			Print("[S7R_TeleportPlayerToRally: PerformAction] Destination failed to set", LogLevel.ERROR);
			return;
		}
		
		fastTravelCmp.FastTravel();
	}
	
	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{	
		IEntity owner = GetOwner();
		if (!owner)
			return;
		
		if (!GetGame().InPlayMode())
			return;
		
		m_ReinsertionManager = S7R_ReinsertionManagerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_ReinsertionManagerComponent));
		
		if (!m_ReinsertionManager)
		{
			Print("[S7R_TeleportPlayerToRally: Init] Could not find ReinsertionManager", LogLevel.ERROR);
			return;
		}
		
		m_RplComp = RplComponent.Cast(owner.FindComponent(RplComponent));
	}
	
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "Reinsert to Rally";
		return true;
	}
}
