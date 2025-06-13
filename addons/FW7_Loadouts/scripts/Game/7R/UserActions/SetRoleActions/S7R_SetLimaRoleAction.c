[BaseContainerProps(description: "7R Set a premade Lima Loadout Action", configRoot: true)]
class S7R_SetLimaRoleAction : S7R_BaseSetRoleAction
{
	[Attribute("1", UIWidgets.ComboBox, category: "Loadouts", enumType: ELimaRoles7R)]
	protected ELimaRoles7R m_eRole;
	
	//------------------------------------------------------------------------------------------------
	override protected bool RetrieveLoadout(out SCR_PlayerArsenalLoadout loadout)
	{
		if (!m_LoadoutManager)
		{
			return false;
		}
		
		array<SCR_PlayerArsenalLoadout> loadouts = m_LoadoutManager.GetLimaLoadouts();
		if (!loadouts)
		{
			return false;
		}
		
		foreach(SCR_PlayerArsenalLoadout candidateLoadout : loadouts)
		{
			S7R_PlayerLimaLoadout limaLoadout = S7R_PlayerLimaLoadout.Cast(candidateLoadout);
			if (limaLoadout && limaLoadout.GetRole() == m_eRole)
			{
				loadout = candidateLoadout;
				return true;
			}
		}
		return false;
	}
}
