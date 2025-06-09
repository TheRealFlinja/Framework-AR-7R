[BaseContainerProps(description: "7R All Factions combined", configRoot: true)]
class S7R_LoadoutMasterConfig: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_FactionLoadouts> m_Factions7R;
	
	//------------------------------------------------------------------------------------------------
	SCR_PlayerArsenalLoadout GetBase7RLoadout(ELoadouts7R factionLoadoutKey = ELoadouts7R.Base)
	{
		S7R_FactionLoadouts factionLoadout = GetLoadoutsFromFactionKey(factionLoadoutKey);
		
		if (!factionLoadout)
		{
			Print(("[S7R_LoadoutMasterConfig: GetBase7RLoadout] Could not find faction " + factionLoadoutKey), LogLevel.WARNING);
			return null;
		}
		
		foreach (SCR_PlayerArsenalLoadout loadout : factionLoadout.GetLoadouts())
		{
			if (loadout.GetSlotID() == "Base7R")
			{
				return loadout;
			}
		}
		
		// No base loadout found with the correct slot ID, look for default
		factionLoadout = GetLoadoutsFromFactionKey();
		
		if (!factionLoadout)
		{
			Print("[S7R_LoadoutMasterConfig: GetBase7RLoadout] Could not find the base faction", LogLevel.ERROR);
			return null;
		}
		
		foreach (SCR_PlayerArsenalLoadout loadout : factionLoadout.GetLoadouts())
		{
			if (loadout.GetSlotID() == "Base7R")
			{
				return loadout;
			}
		}
		
		Print("[S7R_LoadoutMasterConfig: GetBase7RLoadout] Could not find any base role", LogLevel.ERROR);
		return 	null;
	}

	//------------------------------------------------------------------------------------------------
	array<ref S7R_FactionLoadouts> GetFactions7R()
	{
		if (!m_Factions7R)
		{
			Print("[S7R_LoadoutMasterConfig: GetFactions7R] Empty config", LogLevel.ERROR);
			return null;
		}
		
		return m_Factions7R;
	}
	
	//------------------------------------------------------------------------------------------------
	S7R_FactionLoadouts GetLoadoutsFromFactionKey(ELoadouts7R factionKey = ELoadouts7R.Base)
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
}
