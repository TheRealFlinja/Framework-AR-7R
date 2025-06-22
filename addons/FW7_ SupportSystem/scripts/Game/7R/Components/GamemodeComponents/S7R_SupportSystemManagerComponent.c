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
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Supply Configuration")]
	protected ResourceName m_sInfantrySupplyDrop;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Supply Configuration")]
	protected ResourceName m_sMedicalSupplyDrop;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Supply Configuration")]
	protected ResourceName m_sMATSupplyDrop;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Supply Configuration")]
	protected ResourceName m_sHATSupplyDrop;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Supply Configuration")]
	protected ResourceName m_sMMGSupplyDrop;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Supply Configuration")]
	protected ResourceName m_sMortarSupplyDrop;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Supply Configuration")]
	protected ResourceName m_sConstructionSupplyDrop;
	
	[Attribute("20", UIWidgets.Auto, category: "Supply Configuration")]
	protected int m_iSupplyDropUseDelay;
	
	[Attribute("", UIWidgets.ResourceAssignArray, category: "Air Support Configuration")]
	protected ResourceName m_sAircraft;
	
	[Attribute("10", UIWidgets.Auto, category: "Test parameters")]
	protected int m_iSupplySpawnHeight;
	
	[Attribute("5", UIWidgets.Auto, category: "Test parameters")]
	protected int m_iRandomSpawnOffset;
	
	[Attribute("5", UIWidgets.Auto, category: "Test parameters")]
	protected int m_iBaseSpawnDelay;
	
	[Attribute("5", UIWidgets.Auto, category: "Test parameters")]
	protected int m_iSpawnInterval;
	
	protected bool m_bSupplyDropDelayActive = false;
	protected vector m_vSupplyDropMarker;
	protected vector m_vMortarMarker;
	
	protected SCR_LoadoutManager m_LoadoutManager;
	protected S7R_ResourceHandlerComponent m_ResourceHandler;
	
	protected static S7R_SupportSystemManagerComponent s_Instance;
	
	//------------------------------------------------------------------------------------------------
	//! \return
	static S7R_SupportSystemManagerComponent GetInstance()
	{
		return s_Instance;
	}
	
	// Actions
	//------------------------------------------------------------------------------------------------
	//! Call in a supply drop
	bool CallSupplyDrop(int amount, ESupplyBoxType supplyType, int typeID=0)
	{
		ResourceName m_sSupplyDrop;
		vector supplySpawnPosition = m_vSupplyDropMarker;

		supplySpawnPosition = SetHeightFromGround(m_vSupplyDropMarker, m_iSupplySpawnHeight);
		
		switch (supplyType)
		{
			case ESupplyBoxType.InfantrySupply:
				if (m_sInfantrySupplyDrop)
					m_sSupplyDrop = m_sInfantrySupplyDrop;
				break;
			
			case ESupplyBoxType.MATSupply:
				if (m_sMATSupplyDrop)
					m_sSupplyDrop = m_sMATSupplyDrop;
				break;
			
			case ESupplyBoxType.HATSupply:
				if (m_sHATSupplyDrop)
					m_sSupplyDrop = m_sHATSupplyDrop;
				break;
			
			case ESupplyBoxType.MMGSupply:
				if (m_sMMGSupplyDrop)
					m_sSupplyDrop = m_sMMGSupplyDrop;
				break;
			
			case ESupplyBoxType.MortarSupply:
				if (m_sMortarSupplyDrop)
					m_sSupplyDrop = m_sMortarSupplyDrop;
				break;
			
			case ESupplyBoxType.ConstructionSupply:
				if (m_sConstructionSupplyDrop)
					m_sSupplyDrop = m_sConstructionSupplyDrop;
				break;
			
			case ESupplyBoxType.MedicalSupply:
				if (m_sMedicalSupplyDrop)
					m_sSupplyDrop = m_sMedicalSupplyDrop;
				break;
		}
		
		if (!m_sSupplyDrop || !supplySpawnPosition)
			return false;
		
		// Execute Supply Drop
		SetSupplyDropDelayActive(true);
		GetGame().GetCallqueue().CallLater(SetSupplyDropDelayActive, 1000*m_iSupplyDropUseDelay, param1: false);
		
		// Execute Supply Drop
		int spawnDelay = m_iBaseSpawnDelay;
		for (int i = 0; i < amount; i++)
		{
			GetGame().GetCallqueue().CallLater(m_ResourceHandler.SpawnEntityOnPosition, 1000*spawnDelay, param1: m_sSupplyDrop, param2: supplySpawnPosition);
			SetOffsetXZ(supplySpawnPosition, 3, 0);
			spawnDelay += m_iSpawnInterval;
		}
		
		int cost = amount;
		m_iAvailableSupplyBoxes -= cost;
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Call in a supply drop
	bool CanCallSupply(int amount, ESupplyBoxType supplyType, int typeID, out string reason)
	{
		// Replace with delayed init?
		m_LoadoutManager = GetGame().GetLoadoutManager();
		
		if (!m_ResourceHandler || !m_LoadoutManager)
		{
			reason = "Invalid Configuration";
			return false;
		}
		
		// Check relevant position markers present
		if (!m_vSupplyDropMarker)
		{
			reason = "No Supply Marker set";
			return false;
		}
		
		// Check if type of supply is available
		bool typeAvailable = false;
		switch (supplyType)
		{
			case ESupplyBoxType.InfantrySupply:
				if (m_sInfantrySupplyDrop)
					typeAvailable = true;
				break;
			
			case ESupplyBoxType.MATSupply:
				if (m_sMATSupplyDrop)
					typeAvailable = true;
				break;
			
			case ESupplyBoxType.HATSupply:
				if (m_sHATSupplyDrop)
					typeAvailable = true;
				break;
			
			case ESupplyBoxType.MMGSupply:
				if (m_sMMGSupplyDrop)
					typeAvailable = true;
				break;
			
			case ESupplyBoxType.MortarSupply:
				if (m_sMortarSupplyDrop)
					typeAvailable = true;
				break;
			
			case ESupplyBoxType.ConstructionSupply:
				if (m_sConstructionSupplyDrop)
					typeAvailable = true;
				break;
			
			case ESupplyBoxType.MedicalSupply:
				if (m_sMedicalSupplyDrop)
					typeAvailable = true;
				break;
		}
		
		if (!typeAvailable)
		{
			reason = "Supply type not available";
			return false;
		}
		
		// Calculate cost
		int cost = amount;
		if (m_iAvailableSupplyBoxes <= cost)
		{
			reason = "Not enough supplies";
			return false;
		}
		
		if (m_bSupplyDropDelayActive)
		{
			reason = "Recently called in supply drop";
			return false;
		}
		
		return true;
	}
	
	protected void SetSupplyDropDelayActive(bool value)
	{
		if (!value)
		{
			m_bSupplyDropDelayActive = false;
			return;
		}
		
		m_bSupplyDropDelayActive = value;
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
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	bool CallAirstrike()
	{
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	bool CallUAV()
	{
		return false;
	}
	
	// Register and unregister markers
	//------------------------------------------------------------------------------------------------
	void RegisterMarker(vector markerPosition, ESupportMarkerType markerType)
	{
		// Remove or interact with current marker
		switch (markerType)
		{
			case ESupportMarkerType.SupplyDropMarker:
			{
				// TODO: Add a valid position check here
				if (true)
				{
					m_vSupplyDropMarker = markerPosition;
				}
			}
		}
	}
	
	// Helper Functions move to a general helper class?
	//------------------------------------------------------------------------------------------------
	protected void SetOffsetXZ(inout vector pos, int offsetX, int offsetZ)
	{
		pos[0] = pos[0] + offsetX;
		pos[2] = pos[2] + offsetZ;
		
		//SCR_TerrainHelper.GetTerrainNormal(pos);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void CalculateRandomOffsetXZ(vector pos, int offset)
	{
		pos[0] = pos[0] + Math.RandomInt(-1 * offset, offset);
		
		pos[2] = pos[2] + Math.RandomInt(-1 * offset, offset);
	}
	
	//------------------------------------------------------------------------------------------------
	protected vector SetHeightFromGround(vector pos, int height)
	{
		SCR_TerrainHelper.GetTerrainNormal(pos);
		
		pos[1] = pos[1] + height;
		
		return pos;
	}
	
	//------------------------------------------------------------------------------------------------
	override protected void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		
		m_ResourceHandler = S7R_ResourceHandlerComponent.GetInstance();
		m_LoadoutManager = GetGame().GetLoadoutManager();
	}
	
	//------------------------------------------------------------------------------------------------
	// constructor
	//! \param[in] src
	//! \param[in] ent
	//! \param[in] parent
	void S7R_SupportSystemManagerComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		if (!s_Instance)
			s_Instance = this;
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
