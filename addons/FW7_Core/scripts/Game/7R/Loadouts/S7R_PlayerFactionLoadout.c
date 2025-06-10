[BaseContainerProps(configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
modded class SCR_FactionPlayerLoadout : SCR_PlayerLoadout
{
	[Attribute("", UIWidgets.ComboBox, enumType: ERoles7R, category: "7R")]
	protected ERoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	ERoles7R GetRole()
	{
		if (!m_eRole)
			return null;
		
		return m_eRole;
	}
}
