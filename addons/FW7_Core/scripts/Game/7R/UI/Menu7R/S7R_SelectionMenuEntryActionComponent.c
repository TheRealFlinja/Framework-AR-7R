[BaseContainerProps(configRoot: true), SCR_BaseContainerCustomTitleUIInfo("Name")]
class S7R_SelectionMenuEntryActionComponent : SCR_SelectionMenuEntryIconComponent
{
	[Attribute("actionText")]
	protected string m_sActionText;
	
	protected TextWidget m_wActionText;
	
	//------------------------------------------------------------------------------------------------
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		
		m_wActionText = TextWidget.Cast(m_wRoot.FindAnyWidget(m_sActionText));
	}
	
	//------------------------------------------------------------------------------------------------
	void SetActionText(string text)
	{
		if (m_wActionText)
			m_wActionText.SetText(text);
	}
}