/*
modded class SCR_BaseTaskManager : GenericEntity
{
	protected ref map<int, string> m_mTaskIDMap = new map<int, string>();
	
	//------------------------------------------------------------------------------------------------
	int GetTaskIDByName(string nameID)
	{
		return m_mTaskIDMap.GetKeyByValue(nameID);
	}

	//------------------------------------------------------------------------------------------------
	override void RegisterTask(SCR_BaseTask task)
	{
		super.RegisterTask(task);
		
		int taskID = task.GetTaskID();
		string taskName = task.GetTaskNameID();
		
		// Only add to map if nameID is unique and not empty
		if ()
		{
			m_mTaskIDMap.Insert(taskID, taskName);
		}
	}
}
*/
