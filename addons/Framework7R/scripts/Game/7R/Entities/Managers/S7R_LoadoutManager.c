[EntityEditorProps(category: "Framework7R/Entities/Manager", description: "7R Loadoutmanager")]
modded class SCR_LoadoutManagerClass
{
}

/*

TO DO:

	- Add override attributes for groups of roles so multiple factions supported
	- Add proper validation of loadouts

*/

modded class SCR_LoadoutManager : GenericEntity
{	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Loadout Selection")]
	protected ELoadouts7R m_7RFactionLoadoutKey;
	
	[Attribute("", UIWidgets.Auto, category: "7R Loadouts Import")]
	protected ref S7R_LoadoutMasterConfig m_7RLoadoutImports;
	
	protected ref SCR_PlayerArsenalLoadout m_BaseLoadout;
	protected ref S7R_FactionLoadouts m_Loadouts7R;
	
	//------------------------------------------------------------------------------------------------
	//! Get all 7R Loadouts
	protected ref S7R_FactionLoadouts Get7RLoadouts()
	{
	}
	
	//------------------------------------------------------------------------------------------------
	//! Get selected 7R Faction Key for this mission
	ELoadouts7R Get7RLoadoutKey()
	{
		if(!m_7RFactionLoadoutKey)
			return false;
		
		return m_7RFactionLoadoutKey;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Validate Loadout
	//! \param[in] SCR_PlayerArsenalLoadout
	//! \return bool
	protected bool IsValid7RLoadout(SCR_PlayerArsenalLoadout loadout)
	{
		if (loadout.GetFactionKey() != "7R")
		{
			Print("[SCR_Loadouts7RComponent: IsValidLoadout] No faction key found for selected SCR_Role7R", LogLevel.ERROR);
			return false;
		}
		
		return true;
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
	SCR_PlayerArsenalLoadout GetBase7RArsenalLoadout()
	{
		if (!m_BaseLoadout)
		{
			Print("[S7R_LoadoutManager: GetBase7RArsenalLoadout] No base loadout", LogLevel.ERROR);
			return null;
		}
		
		return m_BaseLoadout;
	}
	
	//------------------------------------------------------------------------------------------------
	// Perhaps change the Efunction here?
	override protected void EOnActivate(IEntity owner)
	{
		// Find the base loadout
		if (!m_7RLoadoutImports)
		{
			Print("[S7R_LoadoutManager: EOnActivate] Master Config is empty", LogLevel.ERROR);
			return;
		}
		
		m_BaseLoadout = m_7RLoadoutImports.GetBase7RLoadout(m_7RFactionLoadoutKey);
		
		if (!m_BaseLoadout)
		{
			Print("[S7R_LoadoutManager: EOnActivate] No base loadout found", LogLevel.ERROR);
			return;
		}
		
		m_aPlayerLoadouts.Insert(m_BaseLoadout);
		
		// Find the faction loadouts
		m_Loadouts7R = m_7RLoadoutImports.GetLoadoutsFromFactionKey(m_7RFactionLoadoutKey);
		
		if (!m_Loadouts7R)
		{
			Print("[S7R_LoadoutManager: EOnActivate] Did not find selected faction in master config", LogLevel.ERROR);
			GetOnMappedPlayerLoadoutInfoChanged();
			return;
		}
		
		array<ref SCR_PlayerArsenalLoadout> loadouts = m_Loadouts7R.GetLoadouts();
		
		if (!loadouts)
		{
			Print("[S7R_LoadoutManager: EOnActivate] Did not find loadouts for selected faction in master config", LogLevel.ERROR);
			GetOnMappedPlayerLoadoutInfoChanged();
			return;
		}
		
		foreach (SCR_PlayerArsenalLoadout loadout : loadouts)
		{
			if (!IsValid7RLoadout(loadout))
			{
				continue;
			}
			m_aPlayerLoadouts.Insert(loadout);
		}
		
		GetOnMappedPlayerLoadoutInfoChanged();
	}
}
