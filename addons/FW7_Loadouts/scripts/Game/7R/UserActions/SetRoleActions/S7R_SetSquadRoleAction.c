[BaseContainerProps(description: "7R Set a premade Squad Loadout Action", configRoot: true)]
class S7R_SetSquadRoleAction : S7R_BaseSetRoleAction
{
	[Attribute("1", UIWidgets.ComboBox, category: "Loadouts", enumType: ESquadRoles7R)]
	protected ESquadRoles7R m_eRole;
	
	[Attribute("none", UIWidgets.ComboBox, category: "Loadouts", enumType: EInfSquads7R, desc: "Only needed if specific loadout is needed for a squad")]
	protected EInfSquads7R m_eInfantrySquad;
	
	//------------------------------------------------------------------------------------------------
	override protected bool RetrieveLoadout(out SCR_PlayerArsenalLoadout loadout)
	{
		if (!m_LoadoutManager)
		{
			return false;
		}
		
		array<SCR_PlayerArsenalLoadout> loadouts = m_LoadoutManager.GetSquadLoadouts(m_eInfantrySquad);
		if (!loadouts)
		{
			return false;
		}
		
		foreach(SCR_PlayerArsenalLoadout candidateLoadout : loadouts)
		{
			S7R_PlayerSquadLoadout squadLoadout = S7R_PlayerSquadLoadout.Cast(candidateLoadout);
			if (squadLoadout && squadLoadout.GetRole() == m_eRole)
			{
				loadout = candidateLoadout;
				return true;
			}
		}
		return false;
	}
}
