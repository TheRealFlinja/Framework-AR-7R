modded class SCR_BaseTask : GenericEntity
{
	[Attribute(defvalue: "7R", UIWidgets.Auto, category: "7R")]
	protected FactionKey m_sOwnerFactionKey = "7R";
	protected Faction m_Faction;

	[Attribute("", UIWidgets.Auto, category: "7R", desc: "The ID of the task used for identification in triggers and other systems.")]
    protected string m_sTaskNameID;

    //------------------------------------------------------------------------------------------------
    string GetTaskNameID()
    {
        return m_sTaskNameID;
    }
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		FactionManager factionManager = GetGame().GetFactionManager();
		
		if (factionManager)
		{
			m_Faction = factionManager.GetFactionByKey(m_sOwnerFactionKey);
			if (m_Faction)
			{
				SetName(m_Faction.GetFactionName());
				SetTargetFaction(m_Faction);
			}
			else
				Print("[S7R_BaseTask: EOnInit] Could not find faction key", LogLevel.ERROR);
		}
		else
			Print("[S7R_BaseTask: EOnInit] Could not find faction manager", LogLevel.ERROR);
	}
}
