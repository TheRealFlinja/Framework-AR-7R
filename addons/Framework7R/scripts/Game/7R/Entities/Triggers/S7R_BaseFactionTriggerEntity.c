[EntityEditorProps(category: "Framework7R/Triggers", description: "")]
class S7R_BaseFactionTriggerEntityClass: SCR_BaseTriggerEntityClass
{
};
class S7R_BaseFactionTriggerEntity: SCR_BaseTriggerEntity
{
	[Attribute(defvalue: "1", UIWidgets.Auto, category: "7R")]
	protected int m_iActivateMissionPhase;
	
	protected FactionKey m_sOwnerFactionKey = "7R";
	protected Faction m_OwnerFaction;

	//------------------------------------------------------------------------------------------------
	void SetOwnerFaction(Faction faction)
	{
		m_OwnerFaction = faction;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool ScriptedEntityFilterForQuery(IEntity ent)
	{
		if (!m_OwnerFaction || !IsAlive(ent))
			return false;
		
		FactionAffiliationComponent factionAffiliation = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
		return factionAffiliation && factionAffiliation.GetAffiliatedFaction() == m_OwnerFaction;
	}
	
	//------------------------------------------------------------------------------------------------
	void SCR_BaseFactionTriggerEntity(IEntitySource src, IEntity parent)
	{
		SetEventMask(EntityEvent.INIT);
	}
	
	//------------------------------------------------------------------------------------------------
	override protected event void OnActivate(IEntity ent)
	{
		super.OnActivate(ent);
		
		FactionManager m_factionManager = GetGame().GetFactionManager();
		if (!m_factionManager)
		{
			Print("[S7R_BaseFactionTriggerEntity] OnActivate: No m_factionManager found", LogLevel.ERROR);
		}
		
		m_OwnerFaction = m_factionManager.GetFactionByKey(m_sOwnerFactionKey);
		
		
		S7R_MissionManagerComponent m_missionManager = S7R_MissionManagerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_MissionManagerComponent));
		if (!m_missionManager)
		{
			Print("[S7R_BaseFactionTriggerEntity] OnActivate: Mission Manager not found", LogLevel.ERROR);
			return;
		}
		
		m_missionManager.ActivatePhase(m_iActivateMissionPhase);
	}
};