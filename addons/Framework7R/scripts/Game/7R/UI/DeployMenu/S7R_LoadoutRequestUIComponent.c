//! Component responsible for requesting and visualization of available loadouts in deploy menu.

/*

TO DO:

	- Find hardcoded default for the base loadout

*/
modded class SCR_LoadoutRequestUIComponent : SCR_DeployRequestUIBaseComponent
{
	//------------------------------------------------------------------------------------------------
	//! Show available loadouts in the loadout selector.
	override void ShowAvailableLoadouts(Faction faction)
	{
		if (!m_LoadoutManager)
			return;

		ResetPlayerLoadoutPreview();

		if (!m_LoadoutSelector)
			return;

		m_LoadoutSelector.ClearAll();

		array<ref SCR_BasePlayerLoadout> availableLoadouts = {};
		SCR_BasePlayerLoadout baseLoadout = m_LoadoutManager.GetBase7RArsenalLoadout();
		
		// Add hardcoded default
		if (!baseLoadout)
		{
			return;
		}
		
		// Load assigned loadout if available
		if (m_PlyLoadoutComp.GetAssignedLoadout() && baseLoadout != m_PlyLoadoutComp.GetAssignedLoadout())
		{
			availableLoadouts.Insert(m_PlyLoadoutComp.GetAssignedLoadout())
		}
		
		// Set Base Loadout
		availableLoadouts.Insert(baseLoadout);

		SCR_PlayerArsenalLoadout arsenalLoadout = null;
		foreach (SCR_BasePlayerLoadout loadout : availableLoadouts)
		{
			if (!loadout.IsLoadoutAvailableClient())
				continue;

			if (loadout.IsInherited(SCR_PlayerArsenalLoadout))
				arsenalLoadout = SCR_PlayerArsenalLoadout.Cast(loadout);

			m_LoadoutSelector.AddItem(loadout, loadout.IsLoadoutAvailableClient());
		}
		
		if (!availableLoadouts.IsEmpty())
		{
			if (arsenalLoadout && GetPlayerLoadout() != arsenalLoadout)
				m_PlyLoadoutComp.RequestLoadout(arsenalLoadout);
			else if (!GetPlayerLoadout())
				m_PlyLoadoutComp.RequestLoadout(availableLoadouts[0]);
		}

		GetGame().GetCallqueue().CallLater(RefreshLoadoutPreview, 0, false); // delayed refresh call helps with performance
	}
	
};
