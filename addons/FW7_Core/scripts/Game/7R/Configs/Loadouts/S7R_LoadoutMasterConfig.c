[BaseContainerProps(description: "7R All Factions combined", configRoot: true)]
class S7R_LoadoutMasterConfig: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref SCR_PlayerArsenalLoadout m_Base7RLoadout;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_FactionLoadouts> m_Factions7R;
	
	//------------------------------------------------------------------------------------------------
	SCR_PlayerArsenalLoadout GetBase7RLoadout()
	{
		return m_Base7RLoadout;
	}

	//------------------------------------------------------------------------------------------------
	protected array<ref S7R_FactionLoadouts> GetFactions7R()
	{
		if (!m_Factions7R)
		{
			Print("[S7R_LoadoutMasterConfig: GetFactions7R] Empty config", LogLevel.ERROR);
			return null;
		}
		
		return m_Factions7R;
	}
	
	//------------------------------------------------------------------------------------------------
	S7R_FactionLoadouts GetFactionConfigFromFactionKey(ELoadouts7R factionKey)
	{
		if (!m_Factions7R)
		{
			Print("[S7R_LoadoutMasterConfig: GetLoadoutsFromFactionKey] Empty config", LogLevel.ERROR);
			return null;
		}

		foreach (S7R_FactionLoadouts factionLoadout : m_Factions7R)
		{
			if (factionLoadout.Get7RFactionKey() == factionKey)
			{
				return factionLoadout;
			}
		}
		
		Print("[S7R_LoadoutMasterConfig: GetLoadoutsFromFactionKey] No loadout found with given key", LogLevel.ERROR);
		return null;
	}
	
	//------------------------------------------------------------------------------------------------
	array<SCR_PlayerArsenalLoadout> GetLoadoutsFromFactionKey(ELoadouts7R factionKey)
	{
		if (!m_Factions7R)
		{
			Print("[S7R_LoadoutMasterConfig: GetLoadoutsFromFactionKey] Empty config", LogLevel.ERROR);
			return null;
		}

		foreach (S7R_FactionLoadouts factionLoadout : m_Factions7R)
		{
			if (factionLoadout.Get7RFactionKey() == factionKey)
			{
				return factionLoadout.GetLoadouts();
			}
		}
		
		Print("[S7R_LoadoutMasterConfig: GetLoadoutsFromFactionKey] No loadout found with given key", LogLevel.ERROR);
		return null;
	}
	
	array<SCR_PlayerArsenalLoadout> GetRolesFromFactionAndType(ELoadouts7R factionKey, ERoleTypes7R roletype)
	{
		if (!m_Factions7R)
		{
			Print("[S7R_LoadoutMasterConfig: GetLoadoutsFromFactionKey] Empty config", LogLevel.ERROR);
			return null;
		}

		foreach (S7R_FactionLoadouts factionLoadout : m_Factions7R)
		{
			if (factionLoadout.Get7RFactionKey() == factionKey)
			{
				return factionLoadout.GetLoadoutsFromType(roletype);
			}
		}
		
		Print("[S7R_LoadoutMasterConfig: GetRolesFromFactionAndType] No loadout found with given key", LogLevel.ERROR);
		return null;
	}
}
