[BaseContainerProps(category: "7R/Loadouts", configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
class S7R_PlayerSquadLoadout : SCR_PlayerArsenalLoadout
{	
	[Attribute("1", UIWidgets.ComboBox, enumType: ESquadRoles7R)]
	ESquadRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	ESquadRoles7R GetRole()
	{
		return m_eRole;
	}
}


[BaseContainerProps(category: "7R/Loadouts", configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
class S7R_PlayerPlatoonLoadout : SCR_PlayerArsenalLoadout
{	
	[Attribute("1", UIWidgets.ComboBox, enumType: EPlatoonRoles7R)]
	EPlatoonRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	EPlatoonRoles7R GetRole()
	{
		return m_eRole;
	}
}


[BaseContainerProps(category: "7R/Loadouts", configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
class S7R_PlayerEchoLoadout : SCR_PlayerArsenalLoadout
{	
	[Attribute("1", UIWidgets.ComboBox, enumType: EEchoRoles7R)]
	EEchoRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	EEchoRoles7R GetRole()
	{
		return m_eRole;
	}
}


[BaseContainerProps(category: "7R/Loadouts", configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
class S7R_PlayerSierraLoadout : SCR_PlayerArsenalLoadout
{	
	[Attribute("1", UIWidgets.ComboBox, enumType: ESierraRoles7R)]
	ESierraRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	ESierraRoles7R GetRole()
	{
		return m_eRole;
	}
}


[BaseContainerProps(category: "7R/Loadouts", configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
class S7R_PlayerFoxtrotLoadout : SCR_PlayerArsenalLoadout
{	
	[Attribute("1", UIWidgets.ComboBox, enumType: EFoxtrotRoles7R)]
	EFoxtrotRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	EFoxtrotRoles7R GetRole()
	{
		return m_eRole;
	}
}


[BaseContainerProps(category: "7R/Loadouts", configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
class S7R_PlayerMikeLoadout : SCR_PlayerArsenalLoadout
{	
	[Attribute("1", UIWidgets.ComboBox, enumType: EMikeRoles7R)]
	EMikeRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	EMikeRoles7R GetRole()
	{
		return m_eRole;
	}
}


[BaseContainerProps(category: "7R/Loadouts", configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
class S7R_PlayerLimaLoadout : SCR_PlayerArsenalLoadout
{	
	[Attribute("1", UIWidgets.ComboBox, enumType: ELimaRoles7R)]
	ELimaRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	ELimaRoles7R GetRole()
	{
		return m_eRole;
	}
}


[BaseContainerProps(category: "7R/Loadouts", configRoot: true), BaseContainerCustomTitleField("m_sLoadoutName")]
class S7R_PlayerAviationLoadout : SCR_PlayerArsenalLoadout
{	
	[Attribute("1", UIWidgets.ComboBox, enumType: EAviationRoles7R)]
	EAviationRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	EAviationRoles7R GetRole()
	{
		return m_eRole;
	}
}
