class S7R_LoadArsenalLoadout : SCR_BaseFactionCheckUserAction
{
	[Attribute("1", desc: "If true will try and get the Arsenal component from parent if none found. This is to check if saving is allowed. If no arsenal is found then saving is always true")]
	protected bool m_bAllowGetArsenalFromParent;
	
	[Attribute("1", desc: "")]
	protected string m_sS7RSlotId;
	
	[Attribute("Loadout 1", desc: "")]
	protected string m_sS7RLoadoutLabel;
	
	protected LocalizedString m_sSaveTypeDisplayName;
	
	//~ Ref
	protected SCR_ArsenalComponent m_ArsenalComponent;
	protected SCR_ArsenalManagerComponent m_ArsenalManager;

	
	protected const LocalizedString SPECIFIC_FACTION_CANNOT_PERFORM = "#AR-ArsenalSaveType_FACTION_ITEMS_ONLY_CannotPerformAction";
	
	protected SCR_ResourceConsumer m_ResourceConsumer;
	//~ if the handler exists than supplies are synced with server
	protected SCR_ResourceSystemSubscriptionHandleBase m_ResourceSubscriptionHandleConsumer;
	
	protected RplComponent m_S7RRplComp;
	protected int m_iS7RLastLoadoutTitleCalculation;
	protected int m_iS7RLastActionSupplyCostCalculation;
	protected string m_sS7RLoadoutTitle = "";
	protected string m_sS7RCantPerformReason = "";
	protected bool m_bS7RCanPerformAction;

	
	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		if (SCR_Global.IsEditMode())
			return;
		
		super.Init(pOwnerEntity, pManagerComponent);
		
		SCR_ArsenalManagerComponent.GetArsenalManager(m_ArsenalManager);
		if (!m_ArsenalManager)
			return;
		
		//~ Get Arsenal component
		m_ArsenalComponent = SCR_ArsenalComponent.Cast(GetOwner().FindComponent(SCR_ArsenalComponent));
		if (!m_ArsenalComponent && m_bAllowGetArsenalFromParent && GetOwner().GetParent())
			m_ArsenalComponent = SCR_ArsenalComponent.Cast(GetOwner().GetParent().FindComponent(SCR_ArsenalComponent));
		
		//~ Could not get arsenal
		if (!m_ArsenalComponent)
		{
			Print("SCR_LoadArsenalLoadout is attached to an entity that does not have an arsenal on self or parent (if m_bAllowGetArsenalFromParent is true)!", LogLevel.WARNING);
			return;
		}
		
		m_S7RRplComp = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));

		//~ Call init later to make sure vehicle slot has a parent
		GetGame().GetCallqueue().CallLater(DelayedInit, param1: pOwnerEntity);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void DelayedInit(IEntity owner)
	{
		if (!owner)
			return;
		
		SCR_ResourceComponent resourceComponent = GetResourceComponent();
		if (resourceComponent)
		{
			m_ResourceConsumer = resourceComponent.GetConsumer(EResourceGeneratorID.DEFAULT, EResourceType.SUPPLIES);
			if (!m_ResourceConsumer)
				Print("'S7R_LoadArsenalLoadout' 'EOnInit': '" + GetOwner() + "' arsenal is set to use supplies but the consumer configuration in m_ResourceConsumer is missing", LogLevel.ERROR);
			//~ Temp solution until replication fixed
			else 
				resourceComponent.TEMP_GetOnInteractorReplicated().Insert(TEMP_OnInteractorReplicated);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//~ Temp solution until replication fixed
	protected void TEMP_OnInteractorReplicated()
	{
		SCR_ResourceComponent resourceComponent = SCR_ResourceComponent.FindResourceComponent(GetOwner());
		if (resourceComponent)
			m_ResourceConsumer = resourceComponent.GetConsumer(EResourceGeneratorID.DEFAULT, EResourceType.SUPPLIES);
	}
	
	//------------------------------------------------------------------------------------------------
	protected SCR_ResourceComponent GetResourceComponent()
	{
		IEntity owner = GetOwner();
		if (!owner)
			return null;
		
		return SCR_ResourceComponent.FindResourceComponent(owner);
	}
	
	//------------------------------------------------------------------------------------------------
	override protected bool CanBeShownScript(IEntity user)
	{
		if (!m_ArsenalManager || !super.CanBeShownScript(user))
			return false;
		
		//~ If has arsenal component and arsenal has an inventory. Only show if saving is allowed and not disabled at the start
		if (!m_ArsenalComponent || !m_ArsenalComponent.GetArsenalInventoryComponent() || (m_ArsenalComponent.GetArsenalSaveType() == SCR_EArsenalSaveType.SAVING_DISABLED && !m_ArsenalComponent.IsArsenalSavingDisplayedIfDisabled()))
			return false;
		
		SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
		if (playerController && playerController.IsPossessing())
			return false;
		
		SCR_PlayerLoadoutData playerLoadout = m_ArsenalManager.S7R_GetPlayerLoadoutData_C(m_sS7RSlotId);
		if (!playerLoadout)
			return false;
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override protected bool CanBePerformedScript(IEntity user)
	{
		if (m_ArsenalComponent.GetArsenalSaveType() == SCR_EArsenalSaveType.SAVING_DISABLED)
			return false;
		
		if (!super.CanBePerformedScript(user))
		{
			m_sSaveTypeDisplayName = string.Empty;
			return false;
		}
		
		if (m_ArsenalComponent.GetArsenalSaveType() == SCR_EArsenalSaveType.FACTION_ITEMS_ONLY)
		{
			Faction arsenalFaction = m_ArsenalComponent.GetAssignedFaction();
			
			if (arsenalFaction)
			{
				FactionAffiliationComponent factionAffiliation = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
				if (factionAffiliation && factionAffiliation.GetAffiliatedFaction() != arsenalFaction)
				{
					m_sSaveTypeDisplayName = string.Empty;
					SetCannotPerformReason(WidgetManager.Translate(SPECIFIC_FACTION_CANNOT_PERFORM, arsenalFaction.GetFactionName()));
					return false;
				}
			}
		}
		
		const int now = System.GetTickCount();
		if (now - m_iS7RLastActionSupplyCostCalculation < 1000)
		{
			if (!m_bS7RCanPerformAction)
			{
				SetCannotPerformReason(m_sS7RCantPerformReason);
				return m_bS7RCanPerformAction;
			}
			return m_bS7RCanPerformAction;
		}
		m_iS7RLastActionSupplyCostCalculation = now;

		float loadoutCost;
		if (!GetActionSupplyCost(user, loadoutCost))
		{
			m_sS7RCantPerformReason = "";
			SetCannotPerformReason(m_sS7RCantPerformReason);
			m_bS7RCanPerformAction = false;
			return m_bS7RCanPerformAction;
		}
		
		if (!HasEnoughSupplies(loadoutCost))
		{
			m_sS7RCantPerformReason = "Not enough supplies";
			SetCannotPerformReason(m_sS7RCantPerformReason);
			m_bS7RCanPerformAction = false;
			return m_bS7RCanPerformAction;
		}

		m_sS7RCantPerformReason = "";
		m_bS7RCanPerformAction = true;
		return m_bS7RCanPerformAction;
	}
	
	//------------------------------------------------------------------------------------------------
	void CalculateLoadoutTitle(notnull IEntity user)
	{
		const ChimeraCharacter character = ChimeraCharacter.Cast(user);
		if (!character)
			return;
		
		const int now = System.GetTickCount();
		if (now - m_iS7RLastLoadoutTitleCalculation < 1000)
			return;
		m_iS7RLastLoadoutTitleCalculation = now;

		const int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(character);
		const string playerUID = SCR_ArsenalManagerComponent.S7R_GetPlayerUID(playerId);
		const SCR_PlayerLoadoutData playerLoadoutData = m_ArsenalManager.S7R_GetPlayerLoadoutData_C(m_sS7RSlotId);
		if (!playerLoadoutData)
		{
			m_sS7RLoadoutTitle = "";
			return;
		}
		
		int mostImportantIndex = int.MAX;
		ResourceName mostImportantWeaponPrefab;
		foreach(SCR_WeaponLoadoutData data : playerLoadoutData.Weapons)
		{
			if (data.SlotIdx < mostImportantIndex)
			{
				mostImportantIndex = data.SlotIdx;
				mostImportantWeaponPrefab = data.WeaponPrefab;
			}
		}
		
		if (!mostImportantWeaponPrefab)
		{
			m_sS7RLoadoutTitle = "";
			return;
		}

		const Resource resource = Resource.Load(mostImportantWeaponPrefab);
		if (!resource.IsValid())
			return;
	
		IEntitySource weaponSource = SCR_BaseContainerTools.FindEntitySource(resource);
		if (!weaponSource)
			return;
				
		IEntityComponentSource weaponComponentSource = SCR_BaseContainerTools.FindComponentSource(weaponSource, "WeaponComponent");
		if (!weaponComponentSource)
			return;

		BaseContainer container = weaponComponentSource.GetObject("UIInfo");
		const UIInfo info = UIInfo.Cast(BaseContainerTools.CreateInstanceFromContainer(container));

		m_sS7RLoadoutTitle = WidgetManager.Translate(info.GetName());
	}
	
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{				
		if (!SCR_StringHelper.IsEmptyOrWhiteSpace(m_sSaveTypeDisplayName))
			outName = m_sSaveTypeDisplayName;
		else 
			return super.GetActionNameScript(outName);
		
		return true;
	}	
	
	//------------------------------------------------------------------------------------------------
	override protected void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{		
		if (!m_ArsenalManager || !m_ArsenalComponent || !m_S7RRplComp || m_S7RRplComp.IsProxy())
			return;

		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		if (playerId <= 0)
			return;
		
		super.PerformAction(pOwnerEntity, pUserEntity);
		
		if (AreSuppliesEnabled())
		{
			//~ Failed to consume supplies, meaning there weren't enough supplies for the action
			float loadoutCost;
			if (!GetActionSupplyCost(pUserEntity, loadoutCost) || !ConsumeSuppliesServer(loadoutCost))
				return;
		}
		
		m_ArsenalManager.S7R_LoadPlayerArsenalLoadout_S(m_sS7RSlotId, playerId, GameEntity.Cast(pUserEntity));
	}
	
	//------------------------------------------------------------------------------------------------
	//~ Check if enough supplies to execute the action
	protected bool HasEnoughSupplies(float supplyAmountToCheck)
	{
		if (supplyAmountToCheck <= 0 || !AreSuppliesEnabled())
			return true;
		
		//~ Make sure to create or poke the consumer handler so server sends updates for clients
		if (m_S7RRplComp && m_S7RRplComp.IsProxy())
		{
			if (m_ResourceSubscriptionHandleConsumer)
				m_ResourceSubscriptionHandleConsumer.Poke();
			else
				m_ResourceSubscriptionHandleConsumer = GetGame().GetResourceSystemSubscriptionManager().RequestSubscriptionListenerHandleGraceful(m_ResourceConsumer, Replication.FindId(SCR_ResourcePlayerControllerInventoryComponent.Cast(GetGame().GetPlayerController().FindComponent(SCR_ResourcePlayerControllerInventoryComponent))));
		}
		//~ Simply update if server
		else
		{
			GetGame().GetResourceGrid().UpdateInteractor(m_ResourceConsumer);
		}
		
		//~ Check availability 		
		return m_ResourceConsumer.GetAggregatedResourceValue() >= supplyAmountToCheck;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Get if support station should check for supplies
	//! \return true if should check for supplies
	bool AreSuppliesEnabled()
	{
		SCR_ResourceComponent resourceComponent = GetResourceComponent();
	
		return resourceComponent && resourceComponent.IsResourceTypeEnabled();
	}
	
	//------------------------------------------------------------------------------------------------
	//! Action is executed and supplies are used (Server Only)
	//! \param[in] amount
	//! \return true if there were enough supplies and they are removed
	protected bool ConsumeSuppliesServer(int amount)
	{
		if (amount <= 0 || !AreSuppliesEnabled())
			return true;

		//~ Check if consumption was successful 
		SCR_ResourceConsumtionResponse response = m_ResourceConsumer.RequestConsumtion(amount);
		
		return response.GetReason() == EResourceReason.SUFFICIENT;
	}
	
	//------------------------------------------------------------------------------------------------
	protected bool GetActionSupplyCost(IEntity actionUser, out float cost)
	{
		if (!AreSuppliesEnabled())
		{
			cost = 0;
			return true;
		}
		
		const int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(actionUser);
		SCR_PlayerLoadoutData playerLoadoutData;
		SCR_Faction playerFaction;

		if (!Replication.IsServer())
			playerFaction = SCR_Faction.Cast(SCR_FactionManager.SGetLocalPlayerFaction());
		else
			playerFaction = SCR_Faction.Cast(SCR_FactionManager.SGetPlayerFaction(playerId));
	
		if (!playerFaction)
			return false;
		
		const SCR_CampaignMilitaryBaseComponent closestBase = SCR_GameModeCampaign.GetInstance().GetBaseManager().FindClosestBase(actionUser.GetOrigin());
		if (!closestBase)
			return false;
		
		if (!closestBase.GetIsEntityPresent(actionUser))
			return false;
		
		SCR_LoadoutManager loadoutManager = GetGame().GetLoadoutManager();
		array<ref SCR_BasePlayerLoadout> loadouts = {};
		loadoutManager.GetPlayerLoadoutsByFaction(playerFaction, loadouts);
	
		SCR_PlayerArsenalLoadout arsenalLoadout;
		foreach(SCR_BasePlayerLoadout loadout : loadouts)
		{
			arsenalLoadout = SCR_PlayerArsenalLoadout.Cast(loadout);
			if (arsenalLoadout && arsenalLoadout.m_sS7RSlotId == m_sS7RSlotId)
			{
				cost = SCR_ArsenalManagerComponent.GetLoadoutCalculatedSupplyCost(arsenalLoadout, false, playerId, playerFaction, closestBase.GetOwner());
				return true;
			}
			
		}
		return false;
	}
};
