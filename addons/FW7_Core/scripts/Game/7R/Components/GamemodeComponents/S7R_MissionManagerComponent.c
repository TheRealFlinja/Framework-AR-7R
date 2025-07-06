[EntityEditorProps(category: "7R/Components/GameMode", description: "7R MissionManager Component to the gamemode")]
class S7R_MissionManagerComponentClass: ScriptComponentClass
{
}

/*

TO DO:

	

*/

class S7R_MissionManagerComponent: ScriptComponent
{		
	[Attribute("", UIWidgets.Object, category: "Group Templates")]
	protected ref array<ref ResourceName> m_AIGroupTemplates;
	
	[Attribute("", UIWidgets.Object, category: "Mission Phases")]
	protected ref array<ref S7R_MissionPhase> m_aMissionPhases;
	
	protected bool m_bValidated = false;
	protected int m_iCurrentPhase = 0;
	
	protected RplComponent m_rplComponent;
	protected S7R_AISpawnHandlerComponent m_aiSpawner;
	protected SCR_HintManagerComponent m_hintManager;
	
	protected static S7R_MissionManagerComponent s_Instance;
	
	//------------------------------------------------------------------------------------------------
	//! \return
	static S7R_MissionManagerComponent GetInstance()
	{
		return s_Instance;
	}
	
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
	bool CanPhaseBeActivated(int missionPhaseNumber)
	{
		m_rplComponent = RplComponent.Cast(GetOwner().FindComponent(RplComponent));
		if (!m_rplComponent)
		{
			Print("[S7R_MissionManagerComponent: CanPhaseBeActivated] No Replication component found", LogLevel.ERROR);
			return false;
		}
		
		if (missionPhaseNumber < 0)
		{
			Print("[S7R_MissionManagerComponent: CanPhaseBeActivated] Invalid phase given", LogLevel.ERROR);
			return false;
		}
		
		foreach(S7R_MissionPhase missionPhase: this.m_aMissionPhases)
		{
			if (missionPhase.GetMissionPhaseNumber() == missionPhaseNumber && !missionPhase.HasPhaseBeenActivated())
			{
				return true;
			}
		}
		
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	void ActivatePhase(int missionPhaseNumber)
	{
		// Execute only on server
		if (!m_rplComponent || m_rplComponent.IsProxy())
			return;
		
		if (missionPhaseNumber < 0)
		{
			Print("[S7R_MissionManagerComponent: ActivatePhase] Invalid phase given", LogLevel.ERROR);
			return;
		}
		
		foreach(S7R_MissionPhase missionPhase: this.m_aMissionPhases)
		{
			if (missionPhase.GetMissionPhaseNumber() == missionPhaseNumber)
			{
				missionPhase.ActivatePhase();
				Print("[S7R_MissionManagerComponent: ActivatePhase] Phase activated", LogLevel.DEBUG);
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
		
		m_hintManager = SCR_HintManagerComponent.GetInstance();
		
		if (!m_hintManager)
		{
			Print("[S7R_MissionManagerComponent: OnPostInit] No hint manager found", LogLevel.ERROR);
			return;
		}
		
		m_rplComponent = RplComponent.Cast(GetOwner().FindComponent(RplComponent));
		if (!m_rplComponent)
		{
			Print("[S7R_MissionManagerComponent: OnPostInit] No Replication component found", LogLevel.ERROR);
			return;
		}
		
		GetGame().GetCallqueue().CallLater(ValidateMissionPhases, 5000);
	}
	
	protected void ValidateMissionPhases()
	{
		if (!m_hintManager)
		{
			Print("[S7R_MissionManagerComponent: ValidateMissionPhases] No hint manager found", LogLevel.ERROR);
			return;
		}
		
		m_hintManager.ShowCustom(description: "Validation of Mission Phases started", name: "Mission Manager Validation", duration: 5.0, type: EHint.UNDEFINED);
		
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
	
	//------------------------------------------------------------------------------------------------
	// constructor
	//! \param[in] src
	//! \param[in] ent
	//! \param[in] parent
	void S7R_MissionManagerComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		if (!s_Instance)
			s_Instance = this;
	}
}
