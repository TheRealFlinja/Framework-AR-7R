[EntityEditorProps(category: "Framework7R/Triggers", description: "")]
class S7R_FactionControlTriggerEntityClass: SCR_BaseFactionTriggerEntityClass
{
};
class S7R_FactionControlTriggerEntity: SCR_BaseFactionTriggerEntity
{
	[Attribute(defvalue: "1", UIWidgets.Auto, category: "7R")]
	protected int m_iActivateMissionPhase;
	
	[Attribute("1", UIWidgets.ComboBox, "How should friendly ratio limit be evaluated.", category: "Faction Control Trigger", enums: { ParamEnum("More than", "0"), ParamEnum("Equals to", "1"), ParamEnum("Less than", "2") })]
	protected int m_iRatioMethod;
	
	[Attribute("0.5", UIWidgets.Slider, "Limit for how large portion of trigger entities are friendly.\n\nExamples:\n1 = Only friendlies are present\n0 = Only enemies are present\n0.5 = Equal number of friendlies and enemies\n\nEvaluated only when at least some friendlies or enemies are inside.\nWhen the trigger is empty, condition for ratio = 0 won't activate the trigger.", category: "Faction Control Trigger", params: "0 1 0.1")]
	protected float m_fFriendlyRatioLimit;
	
	[Attribute(desc: "Ignored Faction Keys that won't be used for any calculations for this trigger", category: "Faction Trigger")]
	protected ref array<FactionKey> m_aIgnoredFactionKeys;
	
	protected int m_iFriendlyCount, m_iEnemyCount;
	protected bool m_bResult;
	protected bool m_bEvaluateResult;
	protected bool m_bHasActivated = false;
	
	//------------------------------------------------------------------------------------------------
	//! \param[in] ignoredFactionKeys that will be added to the ignored array
	void AddIgnoredFactionKeys(notnull array<FactionKey> ignoredFactionKeys)
	{
		foreach (FactionKey factionKey : ignoredFactionKeys)
		{
			if (!m_aIgnoredFactionKeys.Contains(factionKey))
				m_aIgnoredFactionKeys.Insert(factionKey);
		}
	}
	
	void GetSideCounts(out int outFriendlyCount, out int outEnemyCount)
	{
		outFriendlyCount = m_iFriendlyCount;
		outEnemyCount = m_iEnemyCount;
	}
	
	override bool ScriptedEntityFilterForQuery(IEntity ent)
	{
		//--- Evaluation round, return the result instantly
		if (m_bEvaluateResult)
		{
			return m_bResult;
		}
		
		//--- No faction defined
		if (!m_OwnerFaction)
		{
			m_iFriendlyCount = 0;
			m_iEnemyCount = 0;
			return false;
		}
		
		//--- Evaluate engine-driven conditions, e.g., entity class
		if (!IsAlive(ent))
			return false;
		
		//--- Increase faction counters
		FactionAffiliationComponent factionAffiliation = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
		if (factionAffiliation)
		{
			Faction entFaction = factionAffiliation.GetAffiliatedFaction();
			if (entFaction)
			{
				if (!m_aIgnoredFactionKeys || m_aIgnoredFactionKeys.IsEmpty() || !m_aIgnoredFactionKeys.Contains(entFaction.GetFactionKey()))
				{
				    if (m_OwnerFaction.IsFactionEnemy(entFaction))
				        m_iEnemyCount++;
				    else
				        m_iFriendlyCount++;
				}
			}
		}
		
		return false;
	}
	
	override protected void OnQueryFinished(bool bIsEmpty)
	{
		//--- Finished evaluation round. Reset variables and start again.
		if (m_bEvaluateResult)
		{
			m_iFriendlyCount = 0;
			m_iEnemyCount = 0;
			m_bEvaluateResult = false;
			return;
		}
		
		m_bResult = false;
		m_bEvaluateResult = true;
		
		//--- Nobody is in the trigger, skip evaluation
		if (m_iFriendlyCount == 0 && m_iEnemyCount == 0)
			return;
		
		float friendlyRatio = m_iFriendlyCount / Math.Max(m_iFriendlyCount + m_iEnemyCount, 1);
		switch (m_iRatioMethod)
		{
			case 0:
			{
				m_bResult = friendlyRatio > m_fFriendlyRatioLimit;
				break;
			}
			case 1:
			{
				m_bResult = float.AlmostEqual(friendlyRatio, m_fFriendlyRatioLimit);
				break;
			}
			case 2:
			{
				m_bResult = friendlyRatio < m_fFriendlyRatioLimit;
				break;
			}
		}
		
		super.OnQueryFinished(bIsEmpty);
	}
	
	override protected event void OnActivate(IEntity ent)
	{
		if (m_bHasActivated)
		{
			return;
		}
		
		super.OnActivate(ent);
		
		S7R_MissionManagerComponent m_missionManager = S7R_MissionManagerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_MissionManagerComponent));
		if (!m_missionManager)
		{
			Print("[S7R_BaseFactionTriggerEntity] OnActivate: Mission Manager not found", LogLevel.ERROR);
			return;
		}
		
		m_missionManager.ActivatePhase(m_iActivateMissionPhase);
		
		m_bHasActivated = true;
	}
};
