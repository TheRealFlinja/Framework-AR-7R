[BaseContainerProps(description: "7R All Loadouts combined", configRoot: true)]
class S7R_FactionLoadouts: ScriptAndConfig
{
	[Attribute("", UIWidgets.ComboBox, enumType: ELoadouts7R)]
	protected ELoadouts7R m_7RFaction;

	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_PlayerSquadLoadout> m_aSquadRoles;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_PlayerPlatoonLoadout> m_aPlatoonRoles;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_PlayerEchoLoadout> m_aEchoRoles;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_PlayerSierraLoadout> m_aSierraRoles;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_PlayerFoxtrotLoadout> m_aFoxtrotRoles;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_PlayerMikeLoadout> m_aMikeRoles;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_PlayerLimaLoadout> m_aLimaRoles;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_PlayerAviationLoadout> m_aAviationRoles;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref S7R_BigBox m_BigBox;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref S7R_SupplyBoxLoadouts m_SupplyBoxes;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref S7R_VehicleLoadouts m_VehicleLoadouts;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref S7R_ScopeBox m_ScopeBox;
	
	//------------------------------------------------------------------------------------------------
	ELoadouts7R Get7RFactionKey()
	{ 
		return m_7RFaction;
	}
	
	//------------------------------------------------------------------------------------------------
	array<SCR_PlayerArsenalLoadout> GetLoadouts()
	{
		array<SCR_PlayerArsenalLoadout> roles = new array<SCR_PlayerArsenalLoadout>;
		
		foreach (S7R_PlayerSquadLoadout loadout : GetSquadLoadouts())
		{
		    if (loadout)
		        roles.Insert(loadout);
		}
		
		foreach (S7R_PlayerPlatoonLoadout loadout : GetPlatoonLoadouts())
		{
		    if (loadout)
		        roles.Insert(loadout);
		}
		
		foreach (S7R_PlayerEchoLoadout loadout : GetEchoLoadouts())
		{
		    if (loadout)
		        roles.Insert(loadout);
		}
		
		foreach (S7R_PlayerSierraLoadout loadout : GetSierraLoadouts())
		{
		    if (loadout)
		        roles.Insert(loadout);
		}
		
		foreach (S7R_PlayerFoxtrotLoadout loadout : GetFoxtrotLoadouts())
		{
		    if (loadout)
		        roles.Insert(loadout);
		}
		
		foreach (S7R_PlayerMikeLoadout loadout : GetMikeLoadouts())
		{
		    if (loadout)
		        roles.Insert(loadout);
		}
		
		foreach (S7R_PlayerLimaLoadout loadout : GetLimaLoadouts())
		{
		    if (loadout)
		        roles.Insert(loadout);
		}
		
		foreach (S7R_PlayerAviationLoadout loadout : GetAviationLoadouts())
		{
		    if (loadout)
		        roles.Insert(loadout);
		}
		
		return roles;
	}
	
	//------------------------------------------------------------------------------------------------
	array<SCR_PlayerArsenalLoadout> GetLoadoutsFromType(ERoleTypes7R roletype)
	{
		array<SCR_PlayerArsenalLoadout> roles = new array<SCR_PlayerArsenalLoadout>;
		
		switch (roletype)
		{
			case ERoleTypes7R.SquadRoles:
			{
				foreach (S7R_PlayerSquadLoadout loadout : GetSquadLoadouts())
				{
				    if (loadout)
						roles.Insert(loadout);
				}
				break;
			}
			case ERoleTypes7R.PlatoonRoles:
			{
				foreach (S7R_PlayerPlatoonLoadout loadout : GetPlatoonLoadouts())
				{
				    if (loadout)
				        roles.Insert(loadout);
				}
				break;
			}
			case ERoleTypes7R.EchoRoles:
			{
				foreach (S7R_PlayerEchoLoadout loadout : GetEchoLoadouts())
				{
				    if (loadout)
				        roles.Insert(loadout);
				}
				break;
			}
			case ERoleTypes7R.SierraRoles:
			{
				foreach (S7R_PlayerSierraLoadout loadout : GetSierraLoadouts())
				{
				    if (loadout)
				        roles.Insert(loadout);
				}
				break;
			}
			case ERoleTypes7R.FoxtrotRoles:
			{
				foreach (S7R_PlayerFoxtrotLoadout loadout : GetFoxtrotLoadouts())
				{
				    if (loadout)
				        roles.Insert(loadout);
				}
				break;
			}
			case ERoleTypes7R.MikeRoles:
			{
				foreach (S7R_PlayerMikeLoadout loadout : GetMikeLoadouts())
				{
				    if (loadout)
				        roles.Insert(loadout);
				}
				break;
			}
			case ERoleTypes7R.LimaRoles:
			{
				foreach (S7R_PlayerLimaLoadout loadout : GetLimaLoadouts())
				{
				    if (loadout)
				        roles.Insert(loadout);
				}
				break;
			}
			case ERoleTypes7R.AviationRoles:
			{
				foreach (S7R_PlayerAviationLoadout loadout : GetAviationLoadouts())
				{
				    if (loadout)
				        roles.Insert(loadout);
				}
				break;
			}
		}
		
		return roles;
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref S7R_PlayerSquadLoadout> GetSquadLoadouts()
	{
		return m_aSquadRoles;
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref S7R_PlayerPlatoonLoadout> GetPlatoonLoadouts()
	{
		return m_aPlatoonRoles;
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref S7R_PlayerEchoLoadout> GetEchoLoadouts()
	{
		return m_aEchoRoles;
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref S7R_PlayerSierraLoadout> GetSierraLoadouts()
	{
		return m_aSierraRoles;
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref S7R_PlayerFoxtrotLoadout> GetFoxtrotLoadouts()
	{
		return m_aFoxtrotRoles;
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref S7R_PlayerMikeLoadout> GetMikeLoadouts()
	{
		return m_aMikeRoles;
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref S7R_PlayerLimaLoadout> GetLimaLoadouts()
	{
		return m_aLimaRoles;
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref S7R_PlayerAviationLoadout> GetAviationLoadouts()
	{
		return m_aAviationRoles;
	}
	
	//------------------------------------------------------------------------------------------------
	S7R_BigBox GetBigBox()
	{
		return m_BigBox;
	}
	
	//------------------------------------------------------------------------------------------------
	S7R_StructSupplyLoadouts GetSupplyLoadout(ESupplyBoxType supplyType, int typeID = 0)
	{
		S7R_SupplyBoxLoadouts supplyBoxConfig = GetSupplyBoxLoadouts();
		
		if(!supplyBoxConfig)
			return null;
		
		return supplyBoxConfig.GetSupplyLoadout(supplyType, typeID);
	}
	
	//------------------------------------------------------------------------------------------------
	S7R_StructVehicleLoadout GetVehicleLoadout(EVehicleLoadoutType vehicleLoadoutType, int typeID = 0)
	{
		S7R_VehicleLoadouts vehicleLoadoutConfig = GetVehicleLoadouts();
		
		if(!vehicleLoadoutConfig)
			return null;
		
		return vehicleLoadoutConfig.GetVehicleLoadout(vehicleLoadoutType, typeID);
	}
	
	//------------------------------------------------------------------------------------------------
	S7R_SupplyBoxLoadouts GetSupplyBoxLoadouts()
	{
		return m_SupplyBoxes;
	}
	
	//------------------------------------------------------------------------------------------------
	S7R_VehicleLoadouts GetVehicleLoadouts()
	{
		return m_VehicleLoadouts;
	}
	
	//------------------------------------------------------------------------------------------------
	S7R_ScopeBox GetScopeBox()
	{
		return m_ScopeBox;
	}
}
