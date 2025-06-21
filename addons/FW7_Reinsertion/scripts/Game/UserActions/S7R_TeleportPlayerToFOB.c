/*

TO DO:
	- Add an area check for hostiles

*/
[BaseContainerProps(description: "7R Reinsertion method: Teleport to FOB Action", configRoot: true)]
class S7R_TeleportPlayerToFOB : SCR_ScriptedUserAction
{
	[Attribute()]
	protected int m_iFOBNumber;
	
	// FOB Information
	protected string m_sFOBKey;
	protected IEntity m_FOBEntity;
	protected vector m_vFOBPosition;
	
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
		
		if (!m_ReinsertionManager.GetFOB(m_iFOBNumber, m_sFOBKey, m_FOBEntity))
		{
			return false;
		}
		
		m_vFOBPosition = m_FOBEntity.GetOrigin();
		if (!m_vFOBPosition)
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
		if (!m_vFOBPosition)
		{
			Print("[S7R_TeleportPlayerToFOB: PerformAction] FOB Position not found", LogLevel.ERROR);
			return;
		}

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
			Print("[S7R_TeleportPlayerToFOB: PerformAction] fastTravelCmp not found", LogLevel.ERROR);
			return;
		}
		
		RplId rplId = fastTravelCmp.FindDestinationId(m_FOBEntity);
		
		if (!rplId.IsValid())
		{
			Print("[S7R_TeleportPlayerToFOB: PerformAction] Invalid rplID", LogLevel.ERROR);
			return;
		}
		
		fastTravelCmp.SetDestination(rplId, m_sFOBKey);
		
		if (fastTravelCmp.GetDestinationName() != m_sFOBKey)
		{
			Print("[S7R_TeleportPlayerToFOB: PerformAction] Destination failed to set", LogLevel.ERROR);
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
			Print("[S7R_TeleportPlayerToFOB: Init] Could not find ReinsertionManager", LogLevel.ERROR);
			return;
		}
		
		m_RplComp = RplComponent.Cast(owner.FindComponent(RplComponent));
	}
	
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		if (!m_sFOBKey)
		{
			outName = "Reinsert to FOB X";
			return true;
		}

		outName = string.Format("Reinsert to FOB %1", m_sFOBKey);
		return true;
	}
}
