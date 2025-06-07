/*

TO DO:

	Add a check if surrounding area is free of players and vehicles

*/
[BaseContainerProps(description: "7R Vehicle Spawn Action", configRoot: true)]
class S7R_SpawnVehicleAction : SCR_ScriptedUserAction
{
	[Attribute("", UIWidgets.ResourceNamePicker, category: "Vehicle Spawn")]
	protected ResourceName m_sVehiclePrefab;
	
	[Attribute("10", UIWidgets.Auto, category: "Vehicle Spawn")]
	protected int m_iAmountOfVehicleAvailable = 0;
	
	[Attribute("", UIWidgets.Auto, category: "Vehicle Spawn")]
	protected string m_sNameSpawnLocation
	
	protected S7R_AISpawnHandlerComponent m_AISpawner;
	protected RplComponent m_RplComp;
	
	protected bool m_bActionStarted;
	
	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		if (!m_sVehiclePrefab)
			return false;
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		if (!m_sVehiclePrefab)
			return false;
		
		IEntity spawnEnt = GetGame().GetWorld().FindEntityByName(m_sNameSpawnLocation);
		
		if (!spawnEnt)
		{
			m_sCannotPerformReason = "Unable to Find spawnpoint"
		}
		
		// Add some recent spawn or area clear checks here
		
		return m_iAmountOfVehicleAvailable > 0;
	}
	
 	//------------------------------------------------------------------------------------------------
 	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
 	{
		if (!m_sVehiclePrefab)
			return;
		
		if (!m_AISpawner)
		{
			Print("[S7R_SpawnVehicleAction: PerformAction] No SCR_AISpawnHandler7RComponent found", LogLevel.ERROR);
			return;
		}
		
		Vehicle vehicle = m_AISpawner.SpawnVehicleUserAction(m_sVehiclePrefab, m_sNameSpawnLocation);
		
		if (!vehicle)
			return;
		
		m_iAmountOfVehicleAvailable -= 1;
		Print("[S7R_SpawnVehicleAction: PerformAction] Vehicle spawned", LogLevel.DEBUG);
 	}
	
	//------------------------------------------------------------------------------------------------
	override void OnActionStart(IEntity pUserEntity)
	{
		if (!m_sVehiclePrefab)
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
		if (!m_sVehiclePrefab)
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
		IEntity owner = GetOwner();
		if (!owner)
			return;
		
		if (!GetGame().InPlayMode())
			return;
		
		m_AISpawner = S7R_AISpawnHandlerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_AISpawnHandlerComponent));
		
		if (!m_AISpawner)
			Print("[S7R_SpawnVehicleAction: Init] No S7R_AISpawnHandlerComponent found", LogLevel.ERROR);
		
		m_RplComp = RplComponent.Cast(owner.FindComponent(RplComponent));
	}
}
