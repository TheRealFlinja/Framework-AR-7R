modded class SCR_BaseTaskManager : GenericEntity
{
	//------------------------------------------------------------------------------------------------
	protected override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		// Only run on master
		if (IsProxy())
		{
			return;
		}
		
		SetFactionForTasks();
	}
	
	void SetFactionForTasks()
	{
		FactionManager factionManager = GetGame().GetFactionManager();
		
		if (!FactionManager)
		{
			Print("[S7R_BaseTaskManager: SetFactionForTasks] Factionmanager not found", LogLevel.ERROR);
			return;
		}
		
		foreach(SCR_BaseTask baseTask : m_aTaskList)
		{
			if (baseTask)
			{
				Faction faction = factionManager.GetFactionByKey(basetask.GetFactionKey());
				SetTaskFaction();
			}
		}
	}
}