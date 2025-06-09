[EntityEditorProps(category: "Framework7R/Entities/GameMode", description: "SCR_Gamemode7R component")]
class S7R_AISpawnHandlerComponentClass: ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

class S7R_AISpawnHandlerComponent: ScriptComponent
{
	//------------------------------------------------------------------------------------------------
	protected ref array<ref ResourceName> m_aAIGroups;
	protected ref array<ResourceName> m_aPrefabsToSpawn;
	protected S7R_ResourceHandlerComponent m_resourceHandler;
	
	//------------------------------------------------------------------------------------------------
	int GetTotalTemplates()
	{
		if (!m_aAIGroups)
		{
			Print("[S7R_AISpawnHandlerComponent: GetTotalTemplates] No templates found", LogLevel.ERROR);
			return 0;
		}
		return m_aAIGroups.Count();
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		
		if (!GetGame().InPlayMode())
			return;
		
		m_resourceHandler = S7R_ResourceHandlerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_ResourceHandlerComponent));
		
		if (!m_resourceHandler)
		{
			Print("[S7R_AISpawnHandlerComponent: OnPostInit] ResourceHandler not found", LogLevel.ERROR);
			return;
		}
		
		S7R_MissionManagerComponent m_missionManagerComponent = S7R_MissionManagerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_MissionManagerComponent));
		
		if (!m_missionManagerComponent)
		{
			Print("[S7R_AISpawnHandlerComponent: OnPostInit] missionManagerComponent not found", LogLevel.ERROR);
			return;
		}
		
		m_aAIGroups = m_missionManagerComponent.GetAIGroupTemplates();
		
		if (!m_aAIGroups)
		{
			Print("[S7R_AISpawnHandlerComponent: OnPostInit] No templates found", LogLevel.ERROR);
			return;
		}
	}

	//------------------------------------------------------------------------------------------------
	// Resource Handler functions
	private Resource GenerateAndValidateResource(string resourceToLoad)
	{
		m_resourceHandler = S7R_ResourceHandlerComponent.Cast(GetOwner().FindComponent(S7R_ResourceHandlerComponent));
		
		if (!m_resourceHandler)
		{
			Print("[S7R_AISpawnHandlerComponent: GenerateAndValidateResource] ResourceHandler not found", LogLevel.ERROR);
			return null;
		}
		
		return m_resourceHandler.GenerateAndValidateResource(resourceToLoad);
	}
	
	private EntitySpawnParams GenerateSpawnParameters(vector spawnPosition)
	{
		m_resourceHandler = S7R_ResourceHandlerComponent.Cast(GetOwner().FindComponent(S7R_ResourceHandlerComponent));
		
		if (!m_resourceHandler)
		{
			Print("[S7R_AISpawnHandlerComponent: GenerateSpawnParameters] ResourceHandler not found", LogLevel.ERROR);
			return null;
		}
		
		return m_resourceHandler.GenerateSpawnParameters(spawnPosition);
	}
	
	//------------------------------------------------------------------------------------------------
	// Get Template based on ID
	ResourceName GetAITemplateFromKey(int key)
	{
		return  m_aAIGroups.Get(key);
	}

	//------------------------------------------------------------------------------------------------
	//Public helper functions
	bool CreateAndAssignWaypointToGroup(SCR_AIGroup group, string waypoint)
	{
		// Create waypoint
		AIWaypoint aiwaypoint = this.CreateWayPoint(waypoint);
		
		if (!aiwaypoint)
		{
			Print("[S7R_AISpawnHandlerComponent: AssignWaypointToGroup] Unable to add waypoint: " + waypoint, LogLevel.ERROR);
			return false;
		}
		
		// Assign waypoint
		group.AddWaypoint(aiwaypoint);
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	//Public helper functions
	bool AssignWaypointToGroup(SCR_AIGroup group, string waypointName)
	{
		// Find waypoint entity
		IEntity waypointEntity = GetGame().GetWorld().FindEntityByName(waypointName);
		
		if (!waypointEntity) {
			Print(("[S7R_AISpawnHandlerComponent: AssignWaypointToGroup] Waypoint does not exist: " + waypointName), LogLevel.ERROR);
			return false;
		}
		
		SCR_AIWaypoint aiwaypoint = SCR_AIWaypoint.Cast(waypointEntity);
		
		if (!aiwaypoint) {
			Print(("[S7R_AISpawnHandlerComponent: AssignWaypointToGroup] Not a valid waypoint " + waypointName), LogLevel.ERROR);
			return false;
		}
		
		// Assign waypoint
		group.AddWaypoint(aiwaypoint);
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	SCR_AIGroup SpawnGroup(int key, string spawnpoint)
	{
		// Generate template
		Resource resource = this.GenerateAndValidateResource(this.GetAITemplateFromKey(key));
		
		if (!resource)
		{
			Print(("[S7R_AISpawnHandlerComponent: SpawnGroup] Unable to load resource for template with ID " + key), LogLevel.ERROR);
			return null;
		}
		
		// Find spawnpoint
		IEntity spawnpointEnt = GetGame().GetWorld().FindEntityByName(spawnpoint);
		//Generate spawn parameters and spawn group
		SCR_AIGroup group = SCR_AIGroup.Cast(GetGame().SpawnEntityPrefab(resource, null, this.GenerateSpawnParameters(spawnpointEnt.GetOrigin())));
	
		if (!group)
		{
			Print("[S7R_AISpawnHandlerComponent: SpawnGroup] Unable to spawn group!", LogLevel.ERROR);
			return null;
		}
		
		return group;
	}
	
	//------------------------------------------------------------------------------------------------
	Vehicle SpawnVehicleUserAction(ResourceName vehicleName, string spawnpoint)
	{
		// Generate template
		Resource resource = this.GenerateAndValidateResource(vehicleName);
		
		if (!resource)
		{
			Print(("[S7R_AISpawnHandlerComponent: SpawnVehicleUserAction] Unable to load resource for vehicle " + vehicleName.GetPath()), LogLevel.ERROR);
			return null;
		}
		
		// Find spawnpoint
		IEntity spawnpointEnt = GetGame().GetWorld().FindEntityByName(spawnpoint);
		//Generate spawn parameters and spawn group
		Vehicle vehicle = Vehicle.Cast(GetGame().SpawnEntityPrefab(resource, null, this.GenerateSpawnParameters(spawnpointEnt.GetOrigin())));
	
		if (!vehicle)
		{
			Print("[S7R_AISpawnHandlerComponent: SpawnVehicleUserAction] Unable to spawn vehicle!", LogLevel.ERROR);
			return null;
		}
		
		return vehicle;
	}
	
	//------------------------------------------------------------------------------------------------
	//Protected Helper Functions
	protected AIWaypoint CreateWayPoint(string waypointName)
	{
		// Find waypoint entity
		IEntity waypointEntity = GetGame().GetWorld().FindEntityByName(waypointName);
		
		if (!waypointEntity) {
			Print(("[S7R_AISpawnHandlerComponent: CreateWayPoint] Waypoint does not exist: " + waypointName), LogLevel.ERROR);
			return null;
		}
		
		// Get Type of waypoint entity
		string waypointType = waypointEntity.Type().ToString();
		// Get position of waypoint entity
		vector waypointPosition = waypointEntity.GetOrigin();

		// Generate the resource
		Resource resource = GenerateAndValidateResource(waypointType);
		
		if (!resource)
		{
			Print(("[S7R_AISpawnHandlerComponent: CreateWayPoint] Unable to load resource for the waypoint: " + waypointType), LogLevel.ERROR);
			return null;
		}
		
		// Generate the spawn parameters and create the waypoint
		AIWaypoint waypoint = AIWaypoint.Cast(GetGame().SpawnEntityPrefab(resource, null, GenerateSpawnParameters(waypointPosition)));
		
		if (!waypoint)
		{
			Print("[S7R_AISpawnHandlerComponent: CreateWayPoint] Unable to create waypoint!", LogLevel.ERROR);
			return null;
		}
		
		return waypoint;
	}
}