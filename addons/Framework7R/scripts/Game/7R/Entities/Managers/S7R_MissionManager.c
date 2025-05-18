[EntityEditorProps(category: "Framework7R/Entities/MissionManager", description: "7R MissionManager")]
class S7R_MissionManagerClass: GenericEntityClass
{
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

class S7R_MissionManager: GenericEntity
{	
	//------------------------------------------------------------------------------------------------
	// Fields
	protected int _currentPhase = 0;
	protected S7R_AISpawnHandlerComponent m_aiSpawner;
	
	[Attribute("", UIWidgets.Object, category: "Group Templates")]
	protected ref array<ref ResourceName> m_AIGroupTemplates;
	
	[Attribute("", UIWidgets.Object, category: "Mission Phases")]
	protected ref array<ref S7R_MissionPhase> m_aMissionPhases;
	
	//------------------------------------------------------------------------------------------------
	//Properties
	int GetCurrentPhase() { return this._currentPhase;}
	void SetCurrentPhase(int currentPhase) { this._currentPhase = currentPhase;}
	
	//------------------------------------------------------------------------------------------------
	/*
	// Overloaded: Both name or number as input
	void ActivatePhase(string missionPhaseName)
	{
		if (missionPhaseName == "")
		{
			Print("[SCR_MissionPhase7R] ActivatePhase, No Phase activated", LogLevel.ERROR);
			return;
		}
		
		foreach(int i, SCR_MissionPhase7R missionPhase: this.m_aMissionPhases)
		{
			if (missionPhase.GetMissionPhaseName() == missionPhaseName)
			{
				missionPhase.ActivatePhase();
				Print("[SCR_MissionPhase7R] Phase activated", LogLevel.DEBUG);
				return;
			}
		}
		Print("[SCR_MissionPhase7R] ActivatePhase, No Phase found", LogLevel.ERROR);
	}
	*/
	
	void ActivatePhase(int missionPhaseNumber)
	{
		if (missionPhaseNumber == 0)
		{
			Print("[SCR_MissionPhase7R] ActivatePhase, No Phase activated", LogLevel.ERROR);
			return;
		}
		
		foreach(int i, S7R_MissionPhase missionPhase: this.m_aMissionPhases)
		{
			if (missionPhase.GetMissionPhaseNumber() == missionPhaseNumber)
			{
				missionPhase.ActivatePhase();
				Print("[SCR_MissionPhase7R] Phase activated", LogLevel.DEBUG);
				return;
			}
		}
		Print("[SCR_MissionPhase7R] ActivatePhase, No Phase found", LogLevel.ERROR);
	}
}
