[EntityEditorProps(category: "Framework7R/Entities/LoadoutManager", description: "SCR_LoadoutManager Component")]
class S7R_LoadoutsComponentClass: ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
/*

TO DO:

*/

class S7R_LoadoutsComponent: ScriptComponent
{
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Loadout Selection")]
	protected ELoadouts7R m_7RLoadout;
	
	[Attribute("", UIWidgets.Auto, desc: "Load the masterconfig of 7R Loadouts here", category: "7R Loadouts Import")]
	protected ref SCR_LoadoutMasterConfig7R m_7RLoadoutImports;
	
	protected ref SCR_Loadouts7R m_Loadouts7R;
	protected SCR_LoadoutManager m_LoadoutManager;
	
	//------------------------------------------------------------------------------------------------
	//! Get 7R Faction Key
	ELoadouts7R Get7RLoadoutKey()
	{
		if(!m_7RLoadout)
			return false;
		
		return m_7RLoadout;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Validate Loadout
	//! \param[in] SCR_Loadouts7R
	//! \return bool
	bool IsValidLoadout(SCR_Loadouts7R loadouts)
	{
		if (!loadouts.GetLoadouts())
		{
			Print("[SCR_Loadouts7RComponent: IsValidLoadout] No loadout found", LogLevel.ERROR);
			return false;
		}
		
		if (loadouts.Get7RFactionKey() == 0)
		{
			Print("[SCR_Loadouts7RComponent: IsValidLoadout] No faction key found for selected SCR_Loadouts7R", LogLevel.ERROR);
			return false;
		}
		
		foreach(SCR_PlayerArsenalLoadout loadout: loadouts.GetLoadouts())
		{
			if (loadout.GetFactionKey() != "7R")
			{
				Print("[SCR_Loadouts7RComponent: IsValidLoadout] No faction key found for selected SCR_Role7R", LogLevel.ERROR);
				return false;
			}
			if (loadout.GetRole() == 0)
			{
				Print("[SCR_Loadouts7RComponent: IsValidLoadout] No role filled in for all selected SCR_Role7R", LogLevel.ERROR);
			}
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	// Add the loadouts to the loadoutmanager
	protected void Add7RLoadouts()
	{
		if (!m_7RLoadout || !m_7RLoadoutImports)
			return;
		
		if (!m_7RLoadoutImports.GetFactions7R())
			return;
		
		// Find selected loadout
		SCR_Loadouts7R selectedLoadouts;
		foreach(SCR_Loadouts7R loadoutsImport: m_7RLoadoutImports.GetFactions7R())
		{
			if (loadoutsImport.Get7RFactionKey() == m_7RLoadout)
			{
				selectedLoadouts = loadoutsImport;
				break;
			}
		}
		
		if (!selectedLoadouts)
		{
			Print("[SCR_Loadouts7RComponent: Add7RLoadouts] No faction loadouts found", LogLevel.ERROR);
			return;
		}
		
		// Check for duplicate keys and filled in factions
		if (!IsValidLoadout(selectedLoadouts))
			return;
		
		// Add loadout to list of player loadouts
		foreach(SCR_PlayerArsenalLoadout loadout: selectedLoadouts.GetLoadouts())
		{
			if (!loadout)
			{
				Print("[SCR_Loadouts7RComponent: Add7RLoadouts] No loadout found", LogLevel.ERROR);
				return;
			}
			
			m_LoadoutManager.AddPlayerLoadout(loadout);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit();
		
		m_LoadoutManager = SCR_LoadoutManager.Cast(owner);
		
		if (!m_LoadoutManager)
		{
			Print("[SCR_Loadouts7RComponent: OnPostInit] m_LoadoutManager empty", LogLevel.ERROR);
			return;
		}

		Add7RLoadouts();
	}
}