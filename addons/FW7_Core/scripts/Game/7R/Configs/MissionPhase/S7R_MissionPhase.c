class S7R_MissionPhase: ScriptAndConfig
{
	//------------------------------------------------------------------------------------------------
	[Attribute("Mission Phase X", UIWidgets.Auto, category: "Identifiers")]
	protected string m_sMissionPhaseName;
	
	[Attribute("1", UIWidgets.Auto, category: "Identifiers")]
	protected int _missionPhaseNumber;
	
	//------------------------------------------------------------------------------------------------
	[Attribute("", UIWidgets.Object, category: "Events")]
	protected ref array<ref IMissionPhaseEvent> m_missionPhaseEvents;
	
	protected int m_iAbsoluteExecutionDelay = 0;
	
	//------------------------------------------------------------------------------------------------
	// Properties
	string GetMissionPhaseName() { return this.m_sMissionPhaseName;}
	int GetMissionPhaseNumber() { return this._missionPhaseNumber;}
	
	//------------------------------------------------------------------------------------------------
	void ActivatePhase()
	{
		foreach(int i, IMissionPhaseEvent missionPhaseEvent: this.m_missionPhaseEvents)
		{
			m_iAbsoluteExecutionDelay += missionPhaseEvent.GetSpawnDelay();
			missionPhaseEvent.UpdateToAbsoluteExecutionDelay(m_iAbsoluteExecutionDelay);
			missionPhaseEvent.ExecuteEvent();
		}
	}
	
	//------------------------------------------------------------------------------------------------
	bool ValidatePhase()
	{
		bool validated = false;
		
		foreach(int i, IMissionPhaseEvent missionPhaseEvent: this.m_missionPhaseEvents)
		{
			validated = missionPhaseEvent.ValidateEvent();
			if (!validated)
			{
				break;
			}
		}
		return validated;
	}
}