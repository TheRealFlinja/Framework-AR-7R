[EntityEditorProps(category: "7R/Components/GameMode", description: "7R MissionManager Component to the gamemode")]
class S7R_MissionManagerComponentClass: ScriptComponentClass
{
}

/*

TO DO:

	

*/

class S7R_MissionManagerComponent: ScriptComponent
{	
	//------------------------------------------------------------------------------------------------
	// Fields
	protected bool m_bValidated = false;
	protected int m_iCurrentPhase = 0;
	protected S7R_AISpawnHandlerComponent m_aiSpawner;
	
	[Attribute("", UIWidgets.Object, category: "Group Templates")]
	protected ref array<ref ResourceName> m_AIGroupTemplates;
	
	[Attribute("", UIWidgets.Object, category: "Mission Phases")]
	protected ref array<ref S7R_MissionPhase> m_aMissionPhases;
	
	//------------------------------------------------------------------------------------------------
	//Properties
	int GetCurrentPhase() { return this.m_iCurrentPhase;}
	void SetCurrentPhase(int currentPhase) { this.m_iCurrentPhase = currentPhase;}
	
	//------------------------------------------------------------------------------------------------
	array<ref ResourceName> GetAIGroupTemplates()
	{
		return m_AIGroupTemplates;
	}
	
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
	
	//------------------------------------------------------------------------------------------------
	void ActivatePhase(int missionPhaseNumber)
	{
		if (missionPhaseNumber < 0)
		{
			Print("[S7R_MissionManagerComponent] ActivatePhase, Invalid phase given", LogLevel.ERROR);
			return;
		}
		
		foreach(S7R_MissionPhase missionPhase: this.m_aMissionPhases)
		{
			if (missionPhase.GetMissionPhaseNumber() == missionPhaseNumber)
			{
				missionPhase.ActivatePhase();
				Print("[S7R_MissionManagerComponent] Phase activated", LogLevel.DEBUG);
				return;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit();
		
		if (!GetGame().InPlayMode())
			return;
		
		GetGame().GetCallqueue().CallLater(ValidateMissionPhases, 5000);
	}
	
	protected void ValidateMissionPhases()
	{
		m_bValidated = false;
		foreach(S7R_MissionPhase missionPhase: this.m_aMissionPhases)
		{
			m_bValidated = missionPhase.ValidatePhase();
			if (!m_bValidated)
			{
				break;
			}
		}
	}
}
