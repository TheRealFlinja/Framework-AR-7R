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
		// Empty current loadouts
		if (!m_LoadoutManager)
			return;

		ResetPlayerLoadoutPreview();

		if (!m_LoadoutSelector)
			return;

		m_LoadoutSelector.ClearAll();

		array<ref SCR_BasePlayerLoadout> availableLoadouts = {};
		Get7RPlayerLoadouts(availableLoadouts);

		SCR_PlayerArsenalLoadout arsenalLoadout = null;
		foreach (SCR_BasePlayerLoadout loadout : availableLoadouts)
		{
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
	
	//------------------------------------------------------------------------------------------------
	//! Fill the loadout list with players' loadouts.
	override void ShowPlayerLoadouts(array<int> playerIds, int slotCount = -1)
	{
		if (!m_wLoadoutList || !m_LoadoutManager)
			return;

		SetListVisible(true);

		ClearLoadoutList();
		
		if (!playerIds || playerIds.IsEmpty())
			return;

		for (int i = 0; i < playerIds.Count(); ++i)
		{
			int pid = playerIds[i];
			SCR_BasePlayerLoadout playerLoadout = m_LoadoutManager.SGetPlayerLoadout(pid);
			CreatePlayerLoadoutButton(playerLoadout, pid, i);
		}
		
		for (int i = playerIds.Count(); i < slotCount; ++i)
		{
			CreateEmptySlot(i);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override protected void UpdateLoadouts(int playerID, bool hasValidLoadout)
	{
		array<ref SCR_BasePlayerLoadout> availableLoadouts = {};
		Get7RPlayerLoadouts(availableLoadouts);
		foreach (SCR_BasePlayerLoadout loadout : availableLoadouts)
		{
			SCR_LoadoutButton loadoutBtn = m_LoadoutSelector.GetButtonForLoadout(loadout);
			if (loadoutBtn)
				loadoutBtn.SetEnabled(loadout.IsLoadoutAvailableClient());
		}
	}
	
	protected void Get7RPlayerLoadouts(out array<ref SCR_BasePlayerLoadout> availableLoadouts)
	{
		// Set Base loadout
		SCR_BasePlayerLoadout baseLoadout = m_LoadoutManager.GetBase7RArsenalLoadout();
		
		// Add hardcoded default
		if (!baseLoadout)
		{
			return;
		}
		
		availableLoadouts.Insert(baseLoadout);

		// Load assigned loadout if available
		if (m_PlyLoadoutComp.GetAssignedLoadout() && baseLoadout != m_PlyLoadoutComp.GetAssignedLoadout())
		{
			availableLoadouts.Insert(m_PlyLoadoutComp.GetAssignedLoadout());
		}
	}
};
