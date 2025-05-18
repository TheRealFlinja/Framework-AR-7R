[BaseContainerProps(description: "7R All Factions combined", configRoot: true)]
class SCR_LoadoutMasterConfig7R: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref SCR_Loadouts7R> m_Factions7R;
	
	//------------------------------------------------------------------------------------------------
	array<ref SCR_Loadouts7R> GetFactions7R()
	{
		if (!m_Factions7R)
			return null;
		
		return m_Factions7R;
	}
}
