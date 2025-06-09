modded class SCR_MissionHeader : MissionHeader
{
	[Attribute()]
	ref S7R_LoadoutEditor_Settings m_S7R_LoadoutEditorSettings;
}

[BaseContainerProps()]
class S7R_LoadoutEditor_Settings
{
	[Attribute("default")]
	string m_iLoadoutId;
}