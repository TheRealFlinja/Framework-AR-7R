[BaseContainerProps(description: "7R Set a premade Sierra Loadout Action", configRoot: true)]
class S7R_SetSierraRoleAction : S7R_BaseSetRoleAction
{
	[Attribute("1", UIWidgets.ComboBox, category: "Loadouts", enumType: ESierraRoles7R)]
	protected ESierraRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	override protected bool RetrieveLoadout(out SCR_PlayerArsenalLoadout loadout)
	{
		if (!m_LoadoutManager)
		{
			return false;
		}
		
		array<SCR_PlayerArsenalLoadout> loadouts = m_LoadoutManager.GetSierraLoadouts();
		if (!loadouts)
		{
			return false;
		}
		
		foreach(SCR_PlayerArsenalLoadout candidateLoadout : loadouts)
		{
			S7R_PlayerSierraLoadout sierraLoadout = S7R_PlayerSierraLoadout.Cast(candidateLoadout);
			if (sierraLoadout && sierraLoadout.GetRole() == m_eRole)
			{
				loadout = candidateLoadout;
				return true;
			}
		}
		return false;
	}
}
