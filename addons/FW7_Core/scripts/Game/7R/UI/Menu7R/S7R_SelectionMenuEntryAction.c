[BaseContainerProps(configRoot: true), SCR_BaseContainerCustomTitleUIInfo("Name")]
class S7R_SelectionMenuEntryAction : SCR_SelectionMenuEntry
{
	protected ResourceName COMMAND_ENTRY_LAYOUT = "{A87A2A3CA0018423}UI/layouts/Common/RadialMenu/SelectionMenuEntryCommand.layout";
	
	[Attribute(desc: "Additional text to entry name")]
	protected string m_sActionText;
	
	//------------------------------------------------------------------------------------------------
	override void SetEntryComponent(SCR_SelectionMenuEntryComponent entryComponent)
	{
		
		S7R_SelectionMenuEntryActionComponent actionEntry = S7R_SelectionMenuEntryActionComponent.Cast(entryComponent);
		if (actionEntry)
		{
			actionEntry.SetActionText(m_sActionText);
		}
		
		super.SetEntryComponent(entryComponent);
	}
	
	//------------------------------------------------------------------------------------------------
	void SetActionText(string text)
	{
		m_sActionText = text;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetActionText()
	{
		return m_sActionText;
	}
	
	//------------------------------------------------------------------------------------------------
	void SCR_SelectionMenuEntryAction()
	{
		m_sCustomLayout = COMMAND_ENTRY_LAYOUT;
	}
}