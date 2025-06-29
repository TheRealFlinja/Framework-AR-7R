modded class SCR_BaseTriggerEntity : ScriptedGameTriggerEntity
{
	[Attribute(defvalue: "0", UIWidgets.ComboBox, category: "7R Task Manager", enumType: ETriggerTaskInteraction)]
	protected ETriggerTaskInteraction m_eTaskInteraction;
	
	//------------------------------------------------------------------------------------------------
	override protected void OnActivate(IEntity ent)
	{
		super.OnActivate(ent);
	}
	
	//------------------------------------------------------------------------------------------------
	ETriggerTaskInteraction GetTaskInteraction()
	{
		return m_eTaskInteraction;
	}
}
