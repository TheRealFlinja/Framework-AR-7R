//! Component responsible for requesting and visualization of available loadouts in deploy menu.
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
		m_LoadoutManager.GetPlayerLoadoutsByFaction(faction, availableLoadouts);

		SCR_PlayerArsenalLoadout arsenalLoadout = null;
		foreach (SCR_BasePlayerLoadout loadout : availableLoadouts)
		{
			if (!loadout.IsLoadoutAvailableClient())
				continue;

			if (loadout.IsInherited(SCR_PlayerArsenalLoadout))
				arsenalLoadout = SCR_PlayerArsenalLoadout.Cast(loadout);
			
			if(arsenalLoadout.GetSlotID() != "Base7R")
				continue;

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

	//------------------------------------------------------------------------------------------------
	override protected void UpdateLoadouts(int playerID, bool hasValidLoadout)
	{
		array<ref SCR_BasePlayerLoadout> availableLoadouts = {};
		m_LoadoutManager.GetPlayerLoadoutsByFaction(m_PlyFactionAffilComp.GetAffiliatedFaction(), availableLoadouts);
		foreach (SCR_BasePlayerLoadout loadout : availableLoadouts)
		{
			SCR_LoadoutButton loadoutBtn = m_LoadoutSelector.GetButtonForLoadout(loadout);
			if (loadoutBtn)
				loadoutBtn.SetEnabled(loadout.IsLoadoutAvailableClient());
		}
	}
};
