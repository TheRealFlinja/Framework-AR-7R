modded class SCR_BaseTriggerEntity : ScriptedGameTriggerEntity
{
	[Attribute(defvalue: "", UIWidgets.CheckBox, category: "7R Mission Manager")]
	protected bool m_bActivateMissionPhase;
	
	[Attribute(defvalue: "1", UIWidgets.Auto, category: "7R Mission Manager")]
	protected int m_iActivateMissionPhase;
	
	//------------------------------------------------------------------------------------------------
	override protected void OnActivate(IEntity ent)
	{
		super.OnActivate(ent);
		
		S7R_MissionManagerComponent missionManager = S7R_MissionManagerComponent.GetInstance();
		
		if (!missionManager)
		{
			Print("[S7R_BaseTriggerEntity: OnActivate] missionManager not found", LogLevel.ERROR);
			return;
		}
		
		if (m_bActivateMissionPhase && missionManager.CanPhaseBeActivated(m_iActivateMissionPhase))
			missionManager.ActivatePhase(m_iActivateMissionPhase);
	}
}
