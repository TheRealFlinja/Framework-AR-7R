modded class SCR_TriggerTask : SCR_AttachableTask
{
	protected SCR_BaseFactionTriggerEntity m_CompletedTrigger;
	protected SCR_BaseFactionTriggerEntity m_FailedTrigger;
	protected SCR_BaseFactionTriggerEntity m_RevealTrigger;
	protected array<SCR_BaseFactionTriggerEntity> m_UpdateTrigger;
	
	//------------------------------------------------------------------------------------------------
	override protected void OnTriggerActivate()
	{
		// Don't want the disgusting original functionality, who does the trigger logic inside the task
		return;
	}
	
	//------------------------------------------------------------------------------------------------
	override protected void OnTriggerDeactivate()
	{
		// Don't want the disgusting original functionality, who does the trigger logic inside the task
		return;
	}
	
	//------------------------------------------------------------------------------------------------
	protected void OnCompleteTriggerActivate()
	{
		if (!GetTaskManager())
			return;
		
		SCR_BaseTaskSupportEntity supportEntity = GetTaskManager().FindSupportEntity(SCR_BaseTaskSupportEntity);
		if (!supportEntity)
			return;
		
		if (m_iTaskCompletionType != EEditorTaskCompletionType.AUTOMATIC)
			return;
		
		supportEntity.FinishTask(this);
	}

	//------------------------------------------------------------------------------------------------
	protected void OnFailedTriggerActivate()
	{
		if (!GetTaskManager())
			return;
		
		SCR_BaseTaskSupportEntity supportEntity = GetTaskManager().FindSupportEntity(SCR_BaseTaskSupportEntity);
		if (!supportEntity)
			return;
		
		if (m_iTaskCompletionType != EEditorTaskCompletionType.AUTOMATIC)
			return;
		
		supportEntity.FailTask(this);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void OnRevealTriggerActivate()
	{
		if (!GetTaskManager())
			return;
		
		SCR_BaseTaskSupportEntity supportEntity = GetTaskManager().FindSupportEntity(SCR_BaseTaskSupportEntity);
		if (!supportEntity)
			return;
		
		if (m_iTaskCompletionType != EEditorTaskCompletionType.AUTOMATIC)
			return;
		
		// Reveal tasks
	}
	
	//------------------------------------------------------------------------------------------------
	override void SetTargetFaction(Faction targetFaction)
	{
		super.SetTargetFaction(targetFaction);
		
		if (m_CompletedTrigger)
			m_CompletedTrigger.SetOwnerFaction(targetFaction);
		
		if (m_FailedTrigger)
			m_FailedTrigger.SetOwnerFaction(targetFaction);
		
		if (m_RevealTrigger)
			m_RevealTrigger.SetOwnerFaction(targetFaction);
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		if (Replication.IsServer())
		{
			IEntity child = GetChildren();
			while (child)
			{
				SCR_BaseFactionTriggerEntity trigger = SCR_BaseFactionTriggerEntity.Cast(child);
				if (trigger)
				{
					switch (trigger.GetTaskInteraction())
					{
						case ETriggerTaskInteraction.Complete:
							m_CompletedTrigger = trigger;
							m_CompletedTrigger.GetOnActivate().Insert(OnCompleteTriggerActivate);
							break;
						case ETriggerTaskInteraction.Fail:
							m_FailedTrigger = trigger;
							m_FailedTrigger.GetOnActivate().Insert(OnFailedTriggerActivate);
							break;
						case ETriggerTaskInteraction.Reveal:
							m_RevealTrigger = trigger;
							m_RevealTrigger.GetOnActivate().Insert(OnRevealTriggerActivate);
							break;
					}
				}
				
				child = child.GetSibling();
			}
			
			if (!SCR_Global.IsEditMode(this))
			{
				Print("SCR_TriggerTask is missing a child of type SCR_BaseFactionTriggerEntity!", LogLevel.ERROR);
			}
		}
	}
}
