// Config for supply boxes
[BaseContainerProps(description: "Supply Box config", configRoot: true)]
class S7R_SupplyBoxLoadouts: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructSupplyLoadouts>  m_aSupplyLoadouts;
}


// Config for the box on spawn
[BaseContainerProps(description: "Big base Box config", configRoot: true)]
class S7R_BigBox: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_StructPrefabAmount>  m_aItems;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aNightItems;
}


// Config for vehicle loadouts
[BaseContainerProps(description: "Vehicle loadouts config", configRoot: true)]
class S7R_VehicleLoadouts: ScriptAndConfig
{
	[Attribute("", UIWidgets.Auto)]
	protected ref array<ref S7R_StructVehicleLoadout>  m_aVehicleLoadouts;
}


// Config for uniforms (Temporary in case loadouts break)
[BaseContainerProps(description: "Uniform box config", configRoot: true)]
class S7R_UniformBox: ScriptAndConfig
{
	[Attribute("0", UIWidgets.Auto, desc: "Unique ID if multiple of type")]
	protected int  m_iLoadout;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array<S7R_StructPrefabAmount>  m_aItems;
}


// Config for scopes (Temporary might be replaced with some action scripts)
[BaseContainerProps(description: "Scope Box config", configRoot: true)]
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


// Struct combining item and amount of items
class S7R_StructPrefabAmount: ScriptAndConfig
{
	[Attribute("", UIWidgets.ResourceNamePicker)]
    protected ResourceName m_Item;
	[Attribute("", UIWidgets.Auto)]
    protected int m_iAmount;
}


// Struct combines loadouts with supply box types
class S7R_StructSupplyLoadouts: ScriptAndConfig
{
	[Attribute("", UIWidgets.ComboBox, enumType: ESupplyBoxType)]
    ESupplyBoxType m_eSupplyType;
	
	[Attribute("0", UIWidgets.Auto, desc: "Unique ID if multiple of type")]
	protected int  m_iSupplyIdentifier;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aItems;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aNightItems;
}


// Struct combines loadouts with vehicle types
class S7R_StructVehicleLoadout: ScriptAndConfig
{
	[Attribute("", UIWidgets.ComboBox, enumType: EVehicleLoadoutType)]
    EVehicleLoadoutType m_eVehicleType;
	
	[Attribute("0", UIWidgets.Auto, desc: "Unique ID if multiple of type")]
	protected int  m_iLoadoutIdentifier;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aItems;
	
	[Attribute("", UIWidgets.Auto)]
	protected ref array <ref S7R_StructPrefabAmount>  m_aNightItems;
}


enum ESupplyBoxType
{
	InfantrySupply = 0,
	MATSupply = 1,
	HATSupply = 2,
	MMGSupply = 3,
	MortarSupply = 4,
	ConstructionSupply = 5,
	
	MedicalSupply = 10
}


enum EVehicleLoadoutType
{
	InfantryVic = 0,
	CommandVic = 1,
	
	EchoMATVic = 10,
	EchoHATVic = 12,
	EchoMMGVic = 13,
	EchoMortarVic = 14,
	
	SierraVic = 20,
	
	FoxtrotAPC = 31,
	FoxtrotIFV = 32,
	FoxtrotMBT = 33,
	
	MikeVic = 40
}
