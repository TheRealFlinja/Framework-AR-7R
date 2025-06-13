[EntityEditorProps(category: "Framework7R/Entities/Manager", description: "7R Loadoutmanager")]
modded class SCR_LoadoutManagerClass
{
}

/*

TO DO:

	- Add proper validation of loadouts

*/

modded class SCR_LoadoutManager : GenericEntity
{	
	
	[Attribute("", UIWidgets.Auto, category: "7R Loadouts Import")]
	protected ref S7R_LoadoutMasterConfig m_7RLoadoutImports;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Loadout Selection")]
	protected ELoadouts7R m_eFactionLoadout7RKey;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eAlphaSquadFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eBravoSquadFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eCharlieSquadFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eDeltaSquadFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_ePlatoonFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eEchoFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eSierraFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eFoxtrotFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eMikeFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eLimaFactionOverride;
	
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R, category: "7R Override Loadout")]
	protected ELoadouts7R m_eAviationFactionOverride;
	
	protected ref SCR_PlayerArsenalLoadout m_BaseLoadout;
	protected ref array<SCR_PlayerArsenalLoadout> m_aAlphaSquadLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aBravoSquadLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aCharlieSquadLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aDeltaSquadLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aPlatoonLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aEchoLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aSierraLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aFoxtrotLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aMikeLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aLimaLoadouts;
	protected ref array<SCR_PlayerArsenalLoadout> m_aAviationLoadouts;
	
	//------------------------------------------------------------------------------------------------
	//! Get Squad 7R Loadouts
	array<SCR_PlayerArsenalLoadout> GetSquadLoadouts(EInfSquads7R squad = EInfSquads7R.Alpha)
	{
		switch (squad)
		{
			case EInfSquads7R.Alpha:
				return m_aAlphaSquadLoadouts;
			case EInfSquads7R.Bravo:
				return m_aBravoSquadLoadouts;
			case EInfSquads7R.Charlie:
				return m_aCharlieSquadLoadouts;
			case EInfSquads7R.Delta:
				return m_aDeltaSquadLoadouts;
		}

		return m_aAlphaSquadLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Alpha Squad 7R Loadouts
	protected array<SCR_PlayerArsenalLoadout> GetAlphaSquadLoadouts()
	{
		return m_aAlphaSquadLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Bravo Squad 7R Loadouts
	protected array<SCR_PlayerArsenalLoadout> GetBravoSquadLoadouts()
	{
		return m_aBravoSquadLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Charlie Squad 7R Loadouts
	protected array<SCR_PlayerArsenalLoadout> GetCharlieSquadLoadouts()
	{
		return m_aCharlieSquadLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Delta Squad 7R Loadouts
	protected array<SCR_PlayerArsenalLoadout> GetDeltaSquadLoadouts()
	{
		return m_aDeltaSquadLoadouts;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Get Platoon 7R Loadouts
	array<SCR_PlayerArsenalLoadout> GetPlatoonLoadouts()
	{
		return m_aPlatoonLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Echo 7R Loadouts
	array<SCR_PlayerArsenalLoadout> GetEchoLoadouts()
	{
		return m_aEchoLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Sierra 7R Loadouts
	array<SCR_PlayerArsenalLoadout> GetSierraLoadouts()
	{
		return m_aSierraLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Foxtrot 7R Loadouts
	array<SCR_PlayerArsenalLoadout> GetFoxtrotLoadouts()
	{
		return m_aFoxtrotLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Mike 7R Loadouts
	array<SCR_PlayerArsenalLoadout> GetMikeLoadouts()
	{
		return m_aMikeLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Lima 7R Loadouts
	array<SCR_PlayerArsenalLoadout> GetLimaLoadouts()
	{
		return m_aLimaLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Aviation 7R Loadouts
	array<SCR_PlayerArsenalLoadout> GetAviationLoadouts()
	{
		return m_aAviationLoadouts;
	}

	//------------------------------------------------------------------------------------------------
	//! Get all 7R Loadouts
	protected array<SCR_PlayerArsenalLoadout> Get7RLoadouts()
	{
	}
	
	//------------------------------------------------------------------------------------------------
	//! Get BigBox class for 
	ELoadouts7R GetCurrent7RFaction()
	{
		return m_7RLoadoutImports.GetFactionConfigFromFactionKey(m_eFactionLoadout7RKey);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Get selected 7R Faction Key for this mission
	ELoadouts7R Get7RLoadoutKey()
	{
		return m_eFactionLoadout7RKey;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Get selected 7R Faction for this mission
	ELoadouts7R GetCurrent7RFaction()
	{
		return m_7RLoadoutImports.GetFactionConfigFromFactionKey(m_eFactionLoadout7RKey);
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
		
		m_BaseLoadout = m_7RLoadoutImports.GetBase7RLoadout();
		
		if (!m_BaseLoadout)
		{
			Print("[S7R_LoadoutManager: EOnActivate] No base loadout found", LogLevel.ERROR);
			return;
		}
		
		// Find the faction loadouts
		m_aPlayerLoadouts.Insert(m_BaseLoadout);
		GetOnMappedPlayerLoadoutInfoChanged();
		
		if (!m_7RLoadoutImports.GetLoadoutsFromFactionKey(m_eFactionLoadout7RKey))
		{
			Print(("[S7R_LoadoutManager: EOnActivate] No loadout found for Factionkey " + m_eFactionLoadout7RKey), LogLevel.ERROR);
			return;
		}
		
		// Init all loadouts
		SetLoadouts(m_aAlphaSquadLoadouts,   m_eAlphaSquadFactionOverride,   m_eFactionLoadout7RKey, ERoleTypes7R.SquadRoles);
		SetLoadouts(m_aBravoSquadLoadouts,   m_eBravoSquadFactionOverride,   m_eFactionLoadout7RKey, ERoleTypes7R.SquadRoles);
		SetLoadouts(m_aCharlieSquadLoadouts, m_eCharlieSquadFactionOverride, m_eFactionLoadout7RKey, ERoleTypes7R.SquadRoles);
		SetLoadouts(m_aDeltaSquadLoadouts,   m_eDeltaSquadFactionOverride,   m_eFactionLoadout7RKey, ERoleTypes7R.SquadRoles);
		SetLoadouts(m_aPlatoonLoadouts,		 m_ePlatoonFactionOverride,		 m_eFactionLoadout7RKey, ERoleTypes7R.PlatoonRoles);
		SetLoadouts(m_aEchoLoadouts,         m_eEchoFactionOverride,         m_eFactionLoadout7RKey, ERoleTypes7R.EchoRoles);
		SetLoadouts(m_aSierraLoadouts,       m_eSierraFactionOverride,       m_eFactionLoadout7RKey, ERoleTypes7R.SierraRoles);
		SetLoadouts(m_aFoxtrotLoadouts,      m_eFoxtrotFactionOverride,      m_eFactionLoadout7RKey, ERoleTypes7R.FoxtrotRoles);
		SetLoadouts(m_aMikeLoadouts,         m_eMikeFactionOverride,         m_eFactionLoadout7RKey, ERoleTypes7R.MikeRoles);
		SetLoadouts(m_aLimaLoadouts,         m_eLimaFactionOverride,         m_eFactionLoadout7RKey, ERoleTypes7R.LimaRoles);
		SetLoadouts(m_aAviationLoadouts,     m_eAviationFactionOverride,     m_eFactionLoadout7RKey, ERoleTypes7R.AviationRoles);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void SetLoadouts(out array<SCR_PlayerArsenalLoadout> loadoutArray, int overrideKey, int defaultKey, int roleType)
	{
	    if (overrideKey != 0)
	    	loadoutArray = m_7RLoadoutImports.GetRolesFromFactionAndType(overrideKey, roleType);
		else
			loadoutArray = m_7RLoadoutImports.GetRolesFromFactionAndType(defaultKey, roleType);
	}
}
