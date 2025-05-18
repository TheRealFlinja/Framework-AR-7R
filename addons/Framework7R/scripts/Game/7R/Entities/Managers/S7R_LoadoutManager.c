[EntityEditorProps(category: "Framework7R/Entities/Manager", description: "7R Loadoutmanager")]
modded class SCR_LoadoutManagerClass
{
}

modded class SCR_LoadoutManager
{	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Loadout Selection")]
	protected ELoadouts7R m_7RLoadout;
	
	[Attribute("", UIWidgets.Auto, category: "7R Loadouts Import")]
	protected ref SCR_LoadoutMasterConfig7R m_7RLoadoutImports;
	
	protected ref SCR_Loadouts7R m_Loadouts7R;

	void AddPlayerLoadout(SCR_BasePlayerLoadout loadout)
	{
		if (!loadout)
		{
			Print("[SCR_LoadoutManager7R: AddPlayerLoadout] No loadout found", LogLevel.ERROR);
			return;
		}
		
		m_aPlayerLoadouts.Insert(loadout);
		
		GetOnMappedPlayerLoadoutInfoChanged();
	}
	
	//------------------------------------------------------------------------------------------------
	//! Returns the first loadout with the provided role, or null if none were found.
	//! \param[in] role
	//! \return
	SCR_PlayerArsenalLoadout GetLoadoutByRole(ERoles7R role)
	{
		foreach(SCR_BasePlayerLoadout loadout: m_aPlayerLoadouts)
		{
			// Sketchy condition, find better way
			if (loadout.ClassName() == "SCR_PlayerArsenalLoadout")
			{
				SCR_PlayerArsenalLoadout loadout7R = SCR_PlayerArsenalLoadout.Cast(loadout);
				if (loadout7R.GetRole() == role)
					return loadout7R;
			}
		}
		
		return null;
	}
	
	//------------------------------------------------------------------------------------------------
	//! TO DO: Should return the base loadout for the current loadout or the basic 7R one if not found
	SCR_PlayerArsenalLoadout GetBase7RArsenalLoadout()
	{
		foreach(SCR_BasePlayerLoadout loadout: m_aPlayerLoadouts)
		{
			// Sketchy condition, find better way
			if (loadout.ClassName() == "SCR_PlayerArsenalLoadout")
			{
				SCR_PlayerArsenalLoadout loadout7R = SCR_PlayerArsenalLoadout.Cast(loadout);
				if (loadout7R.GetSlotID() == "Base7R")
					return loadout7R;
			}
		}
		Print("[S7R_LoadoutManager: GetBase7RArsenalLoadout] No loadout with slotID 'Base' found", LogLevel.ERROR);
		return null;
	}
}
