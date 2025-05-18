[BaseContainerProps(description: "7R All Loadouts combined", configRoot: true)]
class SCR_Loadouts7R: ScriptAndConfig
{
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R)]
	protected ELoadouts7R m_7RFaction;

	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref SCR_PlayerArsenalLoadout> m_aRoles;
	
	ELoadouts7R Get7RFactionKey()
	{ 
		if (!m_7RFaction)
			return null;
		
		return m_7RFaction;
	}
	
	array<ref SCR_PlayerArsenalLoadout> GetLoadouts()
	{
		if (!m_aRoles)
			return null;
		
		return m_aRoles;
	}
}
