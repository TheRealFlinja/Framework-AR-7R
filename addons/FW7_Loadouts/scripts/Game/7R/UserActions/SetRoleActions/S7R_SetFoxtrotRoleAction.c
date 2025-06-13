[BaseContainerProps(description: "7R Set a premade Foxtrot Loadout Action", configRoot: true)]
class S7R_SetFoxtrotRoleAction : S7R_BaseSetRoleAction
{
	[Attribute("1", UIWidgets.ComboBox, category: "Loadouts", enumType: EFoxtrotRoles7R)]
	protected EFoxtrotRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	override protected bool RetrieveLoadout(out SCR_PlayerArsenalLoadout loadout)
	{
		if (!m_LoadoutManager)
		{
			return false;
		}
		
		array<SCR_PlayerArsenalLoadout> loadouts = m_LoadoutManager.GetFoxtrotLoadouts();
		if (!loadouts)
		{
			return false;
		}
		
		foreach(SCR_PlayerArsenalLoadout candidateLoadout : loadouts)
		{
			S7R_PlayerFoxtrotLoadout foxtrotLoadout = S7R_PlayerFoxtrotLoadout.Cast(candidateLoadout);
			if (foxtrotLoadout && foxtrotLoadout.GetRole() == m_eRole)
			{
				loadout = candidateLoadout;
				return true;
			}
		}
		return false;
	}
}
