modded class SCR_BaseTriggerEntity : ScriptedGameTriggerEntity
{
	[Attribute(defvalue: "1", UIWidgets.CheckBox, category: "")]
	protected bool m_bTriggerOnce;

	//------------------------------------------------------------------------------------------------
	override protected void OnActivate(IEntity ent)
	{
		OnFirstChange();
		super.OnActivate(ent);
	}
	
	void OnFirstChange()
	{
		if (m_bTriggerOnce)
	    	Deactivate();
	}
}
