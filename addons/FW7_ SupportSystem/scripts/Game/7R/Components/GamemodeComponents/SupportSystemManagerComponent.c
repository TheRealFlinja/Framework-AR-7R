[EntityEditorProps(category: "7R/Components/GameMode", description: "7R Component that manages all support systems to the gamemode")]
class S7R_SupportSystemManagerComponentClass: ScriptComponentClass
{
}

/*

TO DO:
	Add some hinting for players

*/

class S7R_SupportSystemManagerComponent: ScriptComponent
{
	[Attribute("20", UIWidgets.Auto, category: "Supply")]
	protected int m_iAvailableSupplyBoxes;
	
	[Attribute("20", UIWidgets.Auto, category: "Indirect Fire")]
	protected int m_iMortarSupply;
	
	[Attribute("20", UIWidgets.Auto, category: "Indirect Fire")]
	protected int m_iArtillerySupply;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Air Support")]
	protected IEntity m_FriendlyPlane;
	
	[Attribute("5", UIWidgets.Auto, category: "Air Support")]
	protected int m_iGunRuns;
	
	[Attribute("5", UIWidgets.Auto, category: "Air Support")]
	protected int m_iBombs;
	
	[Attribute("5", UIWidgets.Auto, category: "Air Support")]
	protected int m_iUAVs;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Support System Configuration")]
	protected ResourceName m_sSupplyDrop;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Support System Configuration")]
	protected ResourceName m_sAircraft;
	
	protected vector m_vSupplyDropMarker;
	protected vector m_vMortarMarker;
	
	protected SCR_LoadoutManager m_LoadoutManager;
	protected S7R_ResourceHandlerComponent m_ResourceHandler;
	
	// Actions
	//------------------------------------------------------------------------------------------------
	//! Call in a supply drop
	bool CallSupplyDrop(int amount, ESupplyBoxType supplyType, int typeID=0)
	{
		if (!m_ResourceHandler || !m_LoadoutManager)
			return false;
		
		// Check relevant position markers present
		if (!m_vSupplyDropMarker)
		{
			return false;
		}
		
		// Calculate cost
		int cost = amount;
		
		if (m_iAvailableSupplyBoxes <= cost)
		{
			return false;
		}
		
		// Designate positions with random offsets
		vector adjustedDropPosition = CalculateRandomOffsets(m_vSupplyDropMarker);
		adjustedDropPosition = AdjustHeight(adjustedDropPosition);
		
		// Execute Supply Drop
		m_ResourceHandler.SpawnEntityOnPosition(m_sSupplyDrop, adjustedDropPosition);
		
		m_iAvailableSupplyBoxes -= cost;
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool CallMortar(int amount, EIndirectFireType typeIDF, EAmmunitionTypeIndirectFire ammotype)
	{
		// Check relevant position markers present
		
		// Calculate cost
		int cost = 0;
		
		if (m_iMortarSupply <= cost)
		{
			return false;
		}
		
		// Designate positions with random offsets
		
		// Execute fire mission
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool CallArtillery(EIndirectFireType typeIDF, EAmmunitionTypeIndirectFire ammotype)
	{
		// Get relevant position markers
		
		// Calculate cost
		int cost = 0;
		
		if (m_iArtillerySupply <= cost)
		{
			return false;
		}
		
		// Set random offsets
		
		// Execute fire mission
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool CallGunRun()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool CallAirstrike()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool CallUAV()
	{
		return true;
	}
	
	// Register and unregister markers
	//------------------------------------------------------------------------------------------------
	protected void RegisterMarker(vector markerPosition, ESupportMarkerType markerType)
	{
		// Remove or interact with current marker
		
		// Get coordinates for new marker
		
		// Set marker and store information in this class
	}
	
	// Helper Functions
	//------------------------------------------------------------------------------------------------
	protected vector CalculateRandomOffsets(vector marker)
	{
		return "0 0 0";
	}
	
	//------------------------------------------------------------------------------------------------
	protected vector AdjustHeight(vector location)
	{
		return "0 0 0";
	}
	
	//------------------------------------------------------------------------------------------------
	override protected void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		
		m_ResourceHandler = S7R_ResourceHandlerComponent.Cast(owner.FindComponent(S7R_ResourceHandlerComponent));
		m_LoadoutManager = GetGame().GetLoadoutManager();
	}
}

enum ESupportMarkerType
{
	SupplyDropMarker = 1,
	MortarMarker = 2,
	ArtilleryMarker = 3,
	CASMarker = 4,
	UAVMarker = 5
}
