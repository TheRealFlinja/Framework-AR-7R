[EntityEditorProps(category: "Framework7R/Entities/GameMode", description: "7R Mission GameMode")]
class SCR_Gamemode7RClass: SCR_BaseGameModeClass
{
}

/*

TO DO:

	Class is deprecated, can probably use SCenario gamemode framework

*/

class SCR_Gamemode7R: SCR_BaseGameMode
{
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Loadouts")]
	protected ELoadouts7R m_7RLoadout;
	
	//Required Faction Key properties
	//------------------------------------------------------------------------------------------------
	//Get 7R Faction Key
	ELoadouts7R Get7RLoadoutKey()
	{
		if(!m_7RLoadout)
			return false;
		
		return m_7RLoadout;
	}
}
