// Config for the box on spawn
[BaseContainerProps(category: "7R/Config", description: "Big base Box config", configRoot: true)]
class S7R_BigBox: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_StructPrefabAmount>  m_aItems;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aNightItems;
	
	array<ref S7R_StructPrefabAmount> GetItems()
	{
		return m_aItems;
	}
	
	array<ref S7R_StructPrefabAmount> GetNightItems()
	{
		return m_aNightItems;
	}
}


// Config for supply boxes
[BaseContainerProps(category: "7R/Config", description: "Supply Box config", configRoot: true)]
class S7R_SupplyBoxLoadouts: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructSupplyLoadouts>  m_aSupplyLoadouts;
	
	array<ref S7R_StructSupplyLoadouts> GetSupplyLoadouts()
	{
		return m_aSupplyLoadouts;
	}
	
	ref S7R_StructSupplyLoadouts GetSupplyLoadout(ESupplyBoxType supplyType, int typeID = 0)
	{
		foreach (S7R_StructSupplyLoadouts supplyLoadout: m_aSupplyLoadouts)
		{
			if (supplyLoadout.GetSupplyType() == supplyType && supplyLoadout.GetSupplyTypeID() == typeID)
				return supplyLoadout;
		}
		
		return null;
	}
}


// Config for vehicle loadouts
[BaseContainerProps(category: "7R/Config", description: "Vehicle loadouts config", configRoot: true)]
class S7R_VehicleLoadouts: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_StructVehicleLoadout>  m_aVehicleLoadouts;
	
	ref S7R_StructVehicleLoadout GetVehicleLoadout(EVehicleLoadoutType vehicleLoadoutType, int typeID = 0)
	{
		foreach (S7R_StructVehicleLoadout vehicleLoadout: m_aVehicleLoadouts)
		{
			if (vehicleLoadout.GetVehicleLoadoutType() == vehicleLoadoutType && vehicleLoadout.GetVehicleLoadoutTypeID() == typeID)
				return vehicleLoadout;
		}
		
		return null;
	}
}


// Config for uniforms (Temporary in case loadouts break)
[BaseContainerProps(category: "7R/Config", description: "Uniform box config", configRoot: true)]
class S7R_UniformBox: ScriptAndConfig
{
	[Attribute("0", UIWidgets.Auto, desc: "Unique ID if multiple of type")]
	protected int  m_iLoadout;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<S7R_StructPrefabAmount>  m_aItems;
}


// Config for scopes (Temporary might be replaced with some action scripts)
[BaseContainerProps(category: "7R/Config", description: "Scope Box config", configRoot: true)]
class S7R_ScopeBox: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref ResourceName>  m_aGreenScopes;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref ResourceName>  m_aSpecialMagnifications;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref ResourceName>  m_aMagnifications;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref ResourceName>  m_aNightItems;
}


// MultiSlotConfiguration seems to be the existing struct but cannot retrieve resourcename and amount from it
// Struct combining item and amount of items
[BaseContainerProps(), SCR_BaseContainerResourceTitleField("m_Item")]
class S7R_StructPrefabAmount
{	
	[Attribute("", UIWidgets.ResourceNamePicker)]
    protected ResourceName m_Item;
	[Attribute("", UIWidgets.Auto)]
    protected int m_iAmount;
	
	
	
	//------------------------------------------------------------------------------------------------
	ResourceName GetResourceName()
	{
		return m_Item;
	}
	
	//------------------------------------------------------------------------------------------------
	int GetAmount()
	{
		return m_iAmount;
	}
}


// Struct combines loadouts with supply box types
[BaseContainerProps(), SCR_BaseContainerCustomTitleEnum(enumType: ESupplyBoxType, propertyName: "m_eSupplyType")]
class S7R_StructSupplyLoadouts
{
	[Attribute("", UIWidgets.ComboBox, enumType: ESupplyBoxType)]
    ESupplyBoxType m_eSupplyType;
	
	[Attribute("0", UIWidgets.Auto, desc: "Unique ID if multiple of type")]
	protected int  m_iSupplyIdentifier;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aItems;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aNightItems;
	
	ESupplyBoxType GetSupplyType()
	{
		return m_eSupplyType;
	}
	
	int GetSupplyTypeID()
	{
		return m_iSupplyIdentifier;
	}
	
	array <ref S7R_StructPrefabAmount>  GetItems()
	{
		return m_aItems;
	}
	
	array <ref S7R_StructPrefabAmount>  GetNightItems()
	{
		return m_aNightItems;
	}
}


// Struct combines loadouts with vehicle types
[BaseContainerProps(), SCR_BaseContainerCustomTitleEnum(enumType: EVehicleLoadoutType, propertyName: "m_eVehicleType")]
class S7R_StructVehicleLoadout
{
	[Attribute("", UIWidgets.ComboBox, enumType: EVehicleLoadoutType)]
    protected EVehicleLoadoutType m_eVehicleType;
	
	[Attribute("0", UIWidgets.Auto, desc: "Unique ID if multiple of type")]
	protected int  m_iLoadoutIdentifier;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aItems;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aNightItems;
	
	EVehicleLoadoutType GetVehicleLoadoutType()
	{
		return m_eVehicleType;
	}
	
	int GetVehicleLoadoutTypeID()
	{
		return m_iLoadoutIdentifier;
	}
	
	array <ref S7R_StructPrefabAmount>  GetItems()
	{
		return m_aItems;
	}
	
	array <ref S7R_StructPrefabAmount>  GetNightItems()
	{
		return m_aNightItems;
	}
}
