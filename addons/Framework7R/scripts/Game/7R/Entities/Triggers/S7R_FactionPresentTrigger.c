[EntityEditorProps(category: "Framework7R/Triggers", description: "")]
class S7R_FactionPresentTriggerEntityClass: S7R_BaseFactionTriggerEntityClass
{
};
class S7R_FactionPresentTriggerEntity: S7R_BaseFactionTriggerEntity
{
	protected bool m_bFactionPresent;
	protected bool m_bResult;
	protected bool m_bEvaluateResult;

	override bool ScriptedEntityFilterForQuery(IEntity ent)
	{
		//--- Evaluation round, return the result instantly
		if (m_bEvaluateResult)
		{
			return m_bResult;
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
				m_bFactionPresent = true;
			}
		}
		
		return false;
	}
	override protected void OnQueryFinished(bool bIsEmpty)
	{
		//--- Finished evaluation round. Reset variables and start again.
		if (m_bEvaluateResult)
		{
			m_bFactionPresent = false;
			m_bEvaluateResult = false;
			return;
		}
		
		m_bResult = false;
		m_bEvaluateResult = true;
		
		m_bResult = m_bFactionPresent;
		
		super.OnQueryFinished(bIsEmpty);
	}
};
