/*

TO DO:

	Find a OnInit functionality to load in AISpawner => Maybe change inherited class or put Missionmanager/AISpawner somewhere more logical

*/


class SpawnTemplate: IMissionPhaseEvent
{
	[Attribute("0", UIWidgets.Auto, category: "SpawnParameters")]
	protected int m_iTemplate;
	
	[Attribute("", UIWidgets.Auto, category: "SpawnParameters")]
	protected string m_sSpawnpoint;
	
	[Attribute("", UIWidgets.Auto, category: "SpawnParameters")]
	protected ref array<ref string> m_aWaypoints;
	
	protected S7R_AISpawnHandlerComponent m_AISpawner;
	
	//------------------------------------------------------------------------------------------------
	// Implement Interface functions
	override protected void RealExecuteEvent()
	{		
		//Get AISpawner should move somewhere else for performance
		m_AISpawner = S7R_AISpawnHandlerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_AISpawnHandlerComponent));
		
		if (!m_AISpawner)
		{
			Print("[SpawnTemplate: RealExecuteEvent] m_AISpawner not found", LogLevel.ERROR);
			return;
		}
		
		//Spawn group
		SCR_AIGroup group = m_AISpawner.SpawnGroup(m_iTemplate, m_sSpawnpoint);
		
		// Create AI pathing
		foreach(string waypoint : m_aWaypoints)
		{
			bool success = m_AISpawner.AssignWaypointToGroup(group, waypoint);
			if (!success) { return; }
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override bool ValidateEvent()
	{
		m_AISpawner = S7R_AISpawnHandlerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_AISpawnHandlerComponent));
		
		if (!m_AISpawner)
		{
			Print("[SpawnTemplate: ValidateEvent] m_AISpawner not found", LogLevel.ERROR);
			return false;
		}
		
		bool validated = true;
		if (m_iTemplate < 0 || m_iTemplate > m_AISpawner.GetTotalTemplates())
		{
			Print("[SpawnTemplate: ValidateEvent] Invalid template number", LogLevel.ERROR);
			validated = false;
		}
		
		IEntity spawnpoint = GetGame().GetWorld().FindEntityByName(m_sSpawnpoint);
		
		if (!spawnpoint)
		{
			Print(("[SpawnTemplate: ValidateEvent] Failed to find spawnpoint: " + m_sSpawnpoint), LogLevel.ERROR);
			validated = false;
		}
		
		foreach (int i, string waypointname: m_aWaypoints)
		{
			IEntity waypoint = GetGame().GetWorld().FindEntityByName(waypointname);
			
			if (!waypoint)
			{
				Print(("[SpawnTemplate: ValidateEvent] Failed to find waypoint: " + waypointname), LogLevel.ERROR);
				validated = false;
			}
		}
		
		return validated;
	}
}
