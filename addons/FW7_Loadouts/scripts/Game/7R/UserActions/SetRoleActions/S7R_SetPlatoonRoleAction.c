[BaseContainerProps(description: "7R Set a premade Platoon Loadout Action", configRoot: true)]
class S7R_SetPlatoonRoleAction : S7R_BaseSetRoleAction
{
	[Attribute("1", UIWidgets.ComboBox, category: "Loadouts", enumType: EPlatoonRoles7R)]
	protected EPlatoonRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	override protected bool RetrieveLoadout(out SCR_PlayerArsenalLoadout loadout)
	{
		if (!m_LoadoutManager)
		{
			return false;
		}
		
		array<SCR_PlayerArsenalLoadout> loadouts = m_LoadoutManager.GetPlatoonLoadouts();
		if (!loadouts)
		{
			return false;
		}
		
		foreach(SCR_PlayerArsenalLoadout candidateLoadout : loadouts)
		{
			S7R_PlayerPlatoonLoadout platoonLoadout = S7R_PlayerPlatoonLoadout.Cast(candidateLoadout);
			if (platoonLoadout && platoonLoadout.GetRole() == m_eRole)
			{
				loadout = candidateLoadout;
				return true;
			}
		}
		return false;
	}
}
