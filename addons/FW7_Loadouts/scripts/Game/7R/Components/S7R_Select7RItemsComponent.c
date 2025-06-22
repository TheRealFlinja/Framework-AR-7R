class S7R_Select7RItemsComponentClass : ScriptComponentClass
{
}


class S7R_Select7RItemsComponent : ScriptComponent
{
	[Attribute("", UIWidgets.CheckBox, category: "Big Box", desc: "Check for Big Box Items")]
	protected bool m_bBigBox;
	
	[Attribute("", UIWidgets.CheckBox, category: "Supply Box", desc: "Check for a SupplyLoadout")]
	protected bool m_bSupplyLoadout;
	
	[Attribute("", UIWidgets.ComboBox, category: "Supply Box", enumType: ESupplyBoxType, desc: "Choose the type of supply loadout")]
	protected ESupplyBoxType m_eSupplyLoadoutType;
	
	[Attribute("0", UIWidgets.Auto, category: "Supply Box", desc: "Use the unique identifier for the supply box")]
	protected int m_iSupplyTypeID;
	
	[Attribute("", UIWidgets.CheckBox, category: "Vehicle Loadout", desc: "Only use this if you want to ")]
	protected bool m_bVehicleLoadout;
	
	[Attribute("", UIWidgets.ComboBox, category: "Vehicle Loadout", enumType: EVehicleLoadoutType, desc: "Only use this if you want to ")]
	protected EVehicleLoadoutType m_eVehicleLoadoutType;
	
	[Attribute("0", UIWidgets.Auto, category: "Vehicle Loadout", desc: "Only use this if you want to ")]
	protected int m_iVehicleLoadoutID;
	
	// Only used to override default faction
	[Attribute("0", UIWidgets.ComboBox, category: "Override Faction", enumType: ELoadouts7R, desc: "Only use this if you want supplies from a different faction")]
	protected ELoadouts7R m_eLoadoutOverride;
	
	protected SCR_UniversalInventoryStorageComponent storageCmp;
	
	protected SCR_InventoryStorageManagerComponent storageManager;
	protected SCR_LoadoutManager loadoutManager;
	
	//------------------------------------------------------------------------------------------------
	protected void AddBigBoxItems()
	{
		loadoutManager = GetGame().GetLoadoutManager();
		
		if (!storageCmp || !loadoutManager)
		{
			Print("[S7R_Select7RItemsComponent: AddItemsFromBigBoxConfig] Configuration failed", LogLevel.ERROR);
			return;
		}
		
		S7R_BigBox bigBox = loadoutManager.GetBigBox7RForFaction(m_eLoadoutOverride);
		
		if (!bigBox)
		{
			Print("[S7R_Select7RItemsComponent: AddItemsFromBigBoxConfig] Could not find bigBox", LogLevel.ERROR);
			return;
		}
		
		array<ref S7R_StructPrefabAmount> items = bigBox.GetItems();
		foreach (S7R_StructPrefabAmount item: items)
		{
			if (!AddItem(item))
			{
				Print("[S7R_Select7RItemsComponent: AddItemsFromBigBoxConfig] Could not add item", LogLevel.ERROR);
				return;
			}
		}
		
		
		array<ref S7R_StructPrefabAmount> nightItems = bigBox.GetNightItems();
		foreach (S7R_StructPrefabAmount item: nightItems)
		{
			if (!AddItem(item))
			{
				Print("[S7R_Select7RItemsComponent: AddItemsFromBigBoxConfig] Could not add night item", LogLevel.ERROR);
				return;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void AddSupplyLoadout(ESupplyBoxType supplyType, int typeID = 0)
	{
		loadoutManager = GetGame().GetLoadoutManager();
		
		if (!storageCmp || !loadoutManager)
		{
			Print("[S7R_Select7RItemsComponent: AddSupplyLoadout] Configuration failed", LogLevel.ERROR);
			return;
		}
		
		S7R_StructSupplyLoadouts supplyLoadout = loadoutManager.GetSupplyBox7RForFaction(supplyType, typeID, m_eLoadoutOverride);
		
		if (!supplyLoadout)
		{
			Print("[S7R_Select7RItemsComponent: AddSupplyLoadout] Could not find bigBox", LogLevel.ERROR);
			return;
		}
		
		array<ref S7R_StructPrefabAmount> items = supplyLoadout.GetItems();
		foreach (S7R_StructPrefabAmount item: items)
		{
			if (!AddItem(item))
			{
				Print("[S7R_Select7RItemsComponent: AddSupplyLoadout] Could not add item", LogLevel.ERROR);
				return;
			}
		}
		
		array<ref S7R_StructPrefabAmount> nightItems = supplyLoadout.GetNightItems();
		foreach (S7R_StructPrefabAmount item: items)
		{
			if (!AddItem(item))
			{
				Print("[S7R_Select7RItemsComponent: AddSupplyLoadout] Could not add item", LogLevel.ERROR);
				return;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void AddVehicleLoadout(EVehicleLoadoutType vehicleLoadoutType, int typeID = 0)
	{
		loadoutManager = GetGame().GetLoadoutManager();
		
		if (!storageCmp || !loadoutManager)
		{
			Print("[S7R_Select7RItemsComponent: AddVehicleLoadout] Configuration failed", LogLevel.ERROR);
			return;
		}
		
		S7R_StructVehicleLoadout vehicleLoadout = loadoutManager.GetVehicleLoadout7RForFaction(vehicleLoadoutType, typeID, m_eLoadoutOverride);
		
		if (!vehicleLoadout)
		{
			Print("[S7R_Select7RItemsComponent: AddVehicleLoadout] Could not find bigBox", LogLevel.ERROR);
			return;
		}
		
		array<ref S7R_StructPrefabAmount> items = vehicleLoadout.GetItems();
		foreach (S7R_StructPrefabAmount item: items)
		{
			if (!AddItem(item))
			{
				Print("[S7R_Select7RItemsComponent: AddVehicleLoadout] Could not add item", LogLevel.ERROR);
				return;
			}
		}
		
		array<ref S7R_StructPrefabAmount> nightItems = vehicleLoadout.GetNightItems();
		foreach (S7R_StructPrefabAmount item: items)
		{
			if (!AddItem(item))
			{
				Print("[S7R_Select7RItemsComponent: AddVehicleLoadout] Could not add item", LogLevel.ERROR);
				return;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected bool AddItem(S7R_StructPrefabAmount item)
	{
		if (!storageManager || !storageCmp)
			return false;
		
		ResourceName itemName = item.GetResourceName();
		int amount = item.GetAmount();
		
		if (!itemName)
			return false;
		
		return storageManager.TrySpawnPrefabToStorage(prefab: itemName, storage: storageCmp, count: amount);
	}
	
	//------------------------------------------------------------------------------------------------
	override protected void OnPostInit(IEntity owner)
	{
		if (!GetGame().InPlayMode())
			return;
		
		storageCmp = SCR_UniversalInventoryStorageComponent.Cast(owner.FindComponent(SCR_UniversalInventoryStorageComponent));
		storageManager = SCR_InventoryStorageManagerComponent.Cast(owner.FindComponent(SCR_InventoryStorageManagerComponent));
		loadoutManager = GetGame().GetLoadoutManager();
		
		if (!storageManager || !storageCmp)
		{
			Print("[S7R_Select7RItemsComponent: OnPostInit] Configuration failed", LogLevel.ERROR);
			return;
		}
		
		if (m_bBigBox)
		{
			GetGame().GetCallqueue().CallLater(AddBigBoxItems);
			return;
		}
		
		if (m_bSupplyLoadout)
		{
			GetGame().GetCallqueue().CallLater(AddSupplyLoadout, param1: m_eSupplyLoadoutType, param2: m_iSupplyTypeID);
			return;
		}
		
		if (m_bVehicleLoadout)
		{
			GetGame().GetCallqueue().CallLater(AddVehicleLoadout, param1: m_eVehicleLoadoutType, param2: m_iVehicleLoadoutID);
		}
	}
}
