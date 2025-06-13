[BaseContainerProps(description: "7R Set a premade Aviation Loadout Action", configRoot: true)]
class S7R_SetAviationRoleAction : S7R_BaseSetRoleAction
{
	[Attribute("1", UIWidgets.ComboBox, category: "Loadouts", enumType: EAviationRoles7R)]
	protected EAviationRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	override protected bool RetrieveLoadout(out SCR_PlayerArsenalLoadout loadout)
	{
		if (!m_LoadoutManager)
		{
			return false;
		}
		
		array<SCR_PlayerArsenalLoadout> loadouts = m_LoadoutManager.GetAviationLoadouts();
		if (!loadouts)
		{
			return false;
		}
		
		foreach(SCR_PlayerArsenalLoadout candidateLoadout : loadouts)
		{
			S7R_PlayerAviationLoadout aviationLoadout = S7R_PlayerAviationLoadout.Cast(candidateLoadout);
			if (aviationLoadout && aviationLoadout.GetRole() == m_eRole)
			{
				loadout = candidateLoadout;
				return true;
			}
		}
		return false;
	}
}
