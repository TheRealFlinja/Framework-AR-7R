[EntityEditorProps(category: "7R/UI", description: "Radial menu for 7R Actions")]
class S7R_MenuPlayerComponentClass : ScriptComponentClass
{
}

class S7R_MenuPlayerComponent : ScriptComponent
{
	[Attribute(desc: "Config of pairs of actions and actions menu configs to decide which action opens which menu")]
	protected ResourceName m_sMenuConfigActionPair;
	
	[Attribute()]
	protected ref SCR_RadialMenuController m_RadialMenuController;
	
	protected SCR_RadialMenu m_RadialMenu;
	
	protected ref S7R_Player7RMenuConfig m_MapMenu7RConfig;
	protected ref S7R_Player7RMenuConfig m_Menu7RConfig;
	protected ref S7R_Player7RMenuActionsSetup m_Menu7RPairsConfig;

	protected IEntity m_SelectedEntity;

	protected S7R_MenuManagerComponent m_MenuManager;
	protected SCR_MapRadialUI m_MapContextualMenu;
	protected SCR_InfoDisplayExtended m_CurrentShownAction;
	protected SCR_InfoDisplayExtended m_CurrentShownActionPreview;

	protected string m_sExecutedActionName;

	protected ref array<ref Shape> m_aShapes = {};

	protected bool m_bIsActionExecuting = false;
	protected bool m_bIsActionSelected;
	protected ref SCR_PhysicsHelper m_PhysicsHelper;

	protected string m_sSelectedActionEntry;
	
	// CV
	protected const int FIRST_ITEM_SLOT = 3;
	protected const int SLOT_COUNT = 10;
	
	//! Used to offset the position to spawn waypoint so it is not spawned in terrain
	protected static const float ABOVE_TERRAIN_OFFSET = 0.5;

	//! Maximal range for action in meters
	protected static const float ACTION_VISUAL_RANGE = 10000;
	
	//------------------------------------------------------------------------------------------------
	//! Getters
	//------------------------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------------------------
	bool IsOpened()
	{
		if (!m_RadialMenu)
			return false;

		return m_RadialMenu.IsOpened();
	}

	//------------------------------------------------------------------------------------------------
	bool IsActionSelected()
	{
		return m_bIsActionSelected;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Setters
	//------------------------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------------------------
	void SetShownAction(SCR_InfoDisplayExtended infoDisplay)
	{
		m_CurrentShownAction = infoDisplay;
	}

	//------------------------------------------------------------------------------------------------
	void SetShownActionPreview(SCR_InfoDisplayExtended infoDisplay)
	{
		m_CurrentShownActionPreview = infoDisplay;
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{	
		super.OnPostInit(owner);
		SetEventMask(owner, EntityEvent.INIT);
		
		if (!GetGame().InPlayMode())
			return;
		
		Resource holder = BaseContainerTools.LoadContainer(m_sMenuConfigActionPair);
		if (!holder)
			return;
		
		BaseContainer container = holder.GetResource().ToBaseContainer();
		m_Menu7RPairsConfig = S7R_Player7RMenuActionsSetup.Cast(BaseContainerTools.CreateInstanceFromContainer(container));
		
		if (!m_RadialMenuController || !m_sMenuConfigActionPair)
			return;
		
		m_RadialMenuController.GetOnTakeControl().Insert(OnControllerTakeControl);
		m_RadialMenuController.GetOnControllerChanged().Insert(OnControllerLostControl);
		
		InputManager input = GetGame().GetInputManager();
		foreach (S7R_Player7RConfigActionPair actionConfigPair : m_Menu7RPairsConfig.m_aActionConfigPairs)
		{
			if (!actionConfigPair)
				continue;

			input.AddActionListener(actionConfigPair.GetActionName(), EActionTrigger.DOWN, OpenActionMenu);
		}
			
		m_PhysicsHelper.InitPhysicsHelper();
	}
	
	//------------------------------------------------------------------------------------------------
	void OpenActionMenu()
	{
		if (m_RadialMenuController.IsMenuOpen())
		{
			m_RadialMenuController.CloseMenu();
			return;
		}

		ResourceName configPath;

		foreach (S7R_Player7RConfigActionPair actionConfigPair : m_Menu7RPairsConfig.m_aActionConfigPairs)
		{
			if (!actionConfigPair || !GetGame().GetInputManager().GetActionTriggered(actionConfigPair.GetActionName()))
				continue;

			configPath = actionConfigPair.GetConfig();
			break;
		}

		Resource holder = BaseContainerTools.LoadContainer(configPath);
		if (!holder || !holder.IsValid())
			return;

		BaseContainer container = holder.GetResource().ToBaseContainer();
		m_Menu7RConfig = S7R_Player7RMenuConfig.Cast(BaseContainerTools.CreateInstanceFromContainer(container));

		if (!m_Menu7RConfig)
			return;

		m_RadialMenuController.OnInputOpen();
	}
	
	//------------------------------------------------------------------------------------------------
	//! Call this when menu controller starts to control the menu
	protected void OnControllerTakeControl(SCR_RadialMenuController controller)
	{	
		if (GetGame().GetPlayerController() != GetOwner())
			return;

		// Send/update entries in radial menu when control is gained
		controller.UpdateMenuData();
		SetupPlayerRadialMenu();
	}
	
	//------------------------------------------------------------------------------------------------
	//! Call this when menu controller stops controlling the menu
	protected void OnControllerLostControl(SCR_RadialMenuController controller, bool hasControl)
	{
		if (!hasControl)
			RemoveListenersFromRadial();
	}
	
	//------------------------------------------------------------------------------------------------
	//! Setup and clean up of radial menu on entering and exiting
	//------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------
	//!
	void SetupPlayerRadialMenu()
	{
		BaseGameMode gameMode = GetGame().GetGameMode();
		if (!gameMode)
			return;

		m_RadialMenu = SCR_RadialMenu.GlobalRadialMenu();
		if (!m_RadialMenu)
			return;

		m_RadialMenu.GetOnBeforeOpen().Insert(OnPlayerRadialMenuOpen);
		m_RadialMenu.GetOnClose().Insert(OnPlayerRadialMenuClose);
		m_RadialMenu.GetOnPerform().Insert(OnRadialMenuPerformed);
		m_RadialMenu.GetOnSelect().Insert(OnRadialMenuSelected);
		m_RadialMenu.GetOnOpenFailed().Insert(OnRadialMenuOpenFailed);
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	protected void RemoveListenersFromRadial()
	{
		BaseGameMode gameMode = GetGame().GetGameMode();
		if (!gameMode)
			return;

		if (!m_RadialMenu)
			return;

		m_RadialMenu.GetOnBeforeOpen().Remove(OnPlayerRadialMenuOpen);
		m_RadialMenu.GetOnClose().Remove(OnPlayerRadialMenuClose);
		m_RadialMenu.GetOnPerform().Remove(OnRadialMenuPerformed);
		m_RadialMenu.GetOnSelect().Remove(OnRadialMenuSelected);
		m_RadialMenu.GetOnOpenFailed().Remove(OnRadialMenuOpenFailed);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Radial menu listeners setup
	//------------------------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------------------------
	//!
	void OnPlayerRadialMenuOpen()
	{
		if (!m_RadialMenu || !m_Menu7RConfig)
			return;

		m_RadialMenu.ClearEntries();

		PlayerCamera camera = PlayerCamera.Cast(GetGame().GetCameraManager().CurrentCamera());
		if (!camera)
			return;

		m_SelectedEntity = camera.GetCursorTarget();

		S7R_Player7RMenuCategoryElement rootCategory = m_Menu7RConfig.GetRootCategory();
		if (!rootCategory)
			return;

		AddElementsFromCategory(rootCategory);

		m_bIsActionSelected = false;
	}

	//------------------------------------------------------------------------------------------------
	void OnPlayerRadialMenuClose()
	{
		HideActionPreview();

		m_bIsActionSelected = false;
	}
	
	//------------------------------------------------------------------------------------------------
	//! \param[in] menu
	//! \param[in] entry
	protected void OnRadialMenuSelected(SCR_SelectionMenu menu, SCR_SelectionMenuEntry entry)
	{
		m_bIsActionSelected = false;

		if (!entry || entry.GetId() == string.Empty)
		{
			HideActionPreview();
			return;
		}

		ShowActionPreview(entry.GetId());
	}

	//------------------------------------------------------------------------------------------------
	//! \param[in] menu
	//! \param[in] entry
	protected void OnRadialMenuPerformed(SCR_SelectionMenu menu, SCR_SelectionMenuEntry entry)
	{
		if (!entry)
			return;

		m_bIsActionSelected = false;

		HideActionPreview();
		PrepareExecuteAction(entry.GetId());
	}

	//------------------------------------------------------------------------------------------------
	void OnRadialMenuOpenFailed(SCR_SelectionMenu menu, SCR_ESelectionMenuFailReason reason)
	{
		//for now we handle the empty same as player not being leader since we dont have member commands yet
		//todo: change this when member commands get implemented
		switch (reason)
		{
			case SCR_ESelectionMenuFailReason.MENU_EMPTY:	SCR_NotificationsComponent.SendLocal(ENotification.COMMANDING_NO_RIGHTS); break;
			default: break;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//! Radial menu AddElements helpers
	//------------------------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] category cannot be null
	//! \param[in] rootCategory
	//! \return true if this element is meant to be visible, otherwise false
	bool AddElementsFromCategory(S7R_Player7RMenuCategoryElement category, SCR_SelectionMenuCategoryEntry rootCategory = null)
	{
		array<ref S7R_Player7RMenuBaseElement> elements = category.GetCategoryElements();

		S7R_Player7RMenuCategoryElement elementCategory;
		SCR_SelectionMenuCategoryEntry createdCategory;

		bool canBeShown;
		bool canThisCategoryBeShown;
		foreach (S7R_Player7RMenuBaseElement element : elements)
		{
			elementCategory = S7R_Player7RMenuCategoryElement.Cast(element);
			if (elementCategory)
			{
				createdCategory = SCR_SelectionMenuCategoryEntry.Cast(AddRadialMenuElement(elementCategory, rootCategory));
				if (!createdCategory)
					continue;

				canThisCategoryBeShown = AddElementsFromCategory(elementCategory, createdCategory);
				if (!canThisCategoryBeShown)
				{
					if (rootCategory)
						rootCategory.RemoveEntry(createdCategory);
					else
						m_RadialMenu.RemoveEntry(createdCategory);
				}

				canBeShown = canThisCategoryBeShown || canBeShown;
			}
			else
			{
				canBeShown = AddRadialMenuElement(element, rootCategory) || canBeShown;
			}
		}

		return canBeShown;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] newElement
	//! \param[in] parentCategory
	//! \return
	SCR_SelectionMenuEntry AddRadialMenuElement(S7R_Player7RMenuBaseElement newElement, SCR_SelectionMenuCategoryEntry parentCategory = null)
	{
		S7R_Player7RMenuAction actionElement = S7R_Player7RMenuAction.Cast(newElement);
		if (actionElement)
			return AddActionElement(actionElement, parentCategory);

		S7R_Player7RMenuCategoryElement categoryElement = S7R_Player7RMenuCategoryElement.Cast(newElement);
		if (categoryElement)
			return AddCategoryElement(categoryElement, parentCategory);

		return null;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] action cannot be null
	//! \param[in] parentCategory
	//! \return
	SCR_SelectionMenuEntry AddActionElement(S7R_Player7RMenuAction menuAction, SCR_SelectionMenuCategoryEntry parentCategory = null)
	{
		S7R_MenuManagerComponent menuManager = S7R_MenuManagerComponent.GetInstance();
		if (!menuManager)
			return null;

		SCR_ChimeraCharacter user = SCR_ChimeraCharacter.Cast(SCR_PlayerController.GetLocalControlledEntity());
		if (!user)
			return null;

		if (!menuManager.CanShowAction(menuAction.GetActionName()))
			return null;

		S7R_BaseMenuAction action = menuManager.FindAction(menuAction.GetActionName());

		S7R_SelectionMenuEntryAction entry = new S7R_SelectionMenuEntryAction();

		string displayName = menuAction.GetActionCustomName();
		if (displayName.IsEmpty())
			displayName = menuManager.GetActionDisplayTextByName(menuAction.GetActionName());

		//entry.SetName(displayName);
		bool canPerform = action.CanBePerformed(user);
		entry.SetId(menuAction.GetActionName());
		entry.SetIcon(action.GetIconImageset(), action.GetIconName());
		entry.Enable(canPerform);
		entry.SetActionText(displayName);
		if (!canPerform)
			entry.SetDescription(action.GetCannotPerformReason());

		if (parentCategory)
			parentCategory.AddEntry(entry);
		else
			m_RadialMenu.AddEntry(entry);

		return entry;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] category cannot be null
	//! \param[in] parentCategory
	//! \return
	SCR_SelectionMenuEntry AddCategoryElement(S7R_Player7RMenuCategoryElement category, SCR_SelectionMenuCategoryEntry parentCategory = null)
	{
		SCR_SelectionMenuCategoryEntry newCategory = new SCR_SelectionMenuCategoryEntry();

		newCategory.SetName(category.GetCategoryDisplayText());
		ResourceName imagesetName = category.GetIconImageset();
		string iconName = category.GetIconName();
		if (!imagesetName.IsEmpty() && !iconName.IsEmpty())
			newCategory.SetIcon(imagesetName, iconName);

		if (!parentCategory)
		{
			m_RadialMenu.AddCategoryEntry(newCategory);
			return newCategory;
		}

		parentCategory.AddEntry(newCategory);

		return newCategory;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Radial menu Preview helpers
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	//! If a command is currently being displayed, hide/delete it
	protected void DeleteShownAction()
	{
		if (!m_CurrentShownAction)
			return;

		SCR_HUDManagerComponent hudManager = SCR_HUDManagerComponent.GetHUDManager();
		if (!hudManager)
			return;

		hudManager.StopDrawing(m_CurrentShownAction);
		m_CurrentShownAction = null;
	}

	//------------------------------------------------------------------------------------------------
	//! Hide command preview
	void HideActionPreview()
	{
		m_bIsActionSelected = false;

		if (!m_CurrentShownActionPreview)
			return;

		SCR_HUDManagerComponent hudManager = SCR_HUDManagerComponent.GetHUDManager();
		if (!hudManager)
			return;

		hudManager.StopDrawing(m_CurrentShownActionPreview);
		m_CurrentShownActionPreview = null;
	}

	//------------------------------------------------------------------------------------------------
	//! Prepare the action to be shown
	//! \param[in] actionName
	void ShowActionPreview(string actionName)
	{
		if (m_CurrentShownActionPreview)
			HideActionPreview();

		if (actionName.IsEmpty())
			return;

		m_sSelectedActionEntry = actionName;
		m_bIsActionSelected = true;

		S7R_MenuManagerComponent menuManager = S7R_MenuManagerComponent.GetInstance();
		if (!menuManager)
			return;

		S7R_BaseMenuAction action = S7R_BaseMenuAction.Cast(menuManager.FindAction(m_sSelectedActionEntry));
		if (!action || !action.CanShowPreview())
			return;

		action.VisualizeActionPreview(vector.Zero);

		if (!m_CurrentShownActionPreview)
			return;

		SCR_PlacedCommandInfoDisplay actionInfo = SCR_PlacedCommandInfoDisplay.Cast(m_CurrentShownActionPreview);
		if (actionInfo)
			actionInfo.SetCanUpdatePosition(true);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Action Execution functions
	//------------------------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionName
	void PrepareExecuteAction(string actionName, vector targetPosition = "0 0 0")
	{
		//if another action is waiting for trace, do nothing
		if (m_bIsActionExecuting || actionName.IsEmpty())
			return;

		m_sExecutedActionName = actionName;

		if (targetPosition != vector.Zero)
		{
			ExecuteAction(targetPosition, null);
			return;
		}

		PhysicsActionTrace();

		if (m_PhysicsHelper)
		{
			m_PhysicsHelper.GetOnTraceFinished().Insert(ExecuteAction);

			//prevent other actions being executed while this one is waiting for trace
			m_bIsActionExecuting = true;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] targetPosition
	//! \param[in] tracedEntity
	void ExecuteAction(vector targetPosition, IEntity tracedEntity)
	{
		m_bIsActionExecuting = false;
		if (m_PhysicsHelper)
		{
			m_PhysicsHelper.GetOnTraceFinished().Remove(ExecuteAction);
			m_PhysicsHelper = null;
		}

		S7R_MenuManagerComponent menuManager = S7R_MenuManagerComponent.GetInstance();
		if (!menuManager)
			return;

		int playerID = SCR_PlayerController.GetLocalPlayerId();

		RplId cursorTargetRplID;

		int actionIndex = menuManager.FindActionIndex(m_sExecutedActionName);

		RplComponent rplComp;
		if (m_SelectedEntity)
		{
			rplComp = RplComponent.Cast(m_SelectedEntity.FindComponent(RplComponent));
			if (rplComp)
				cursorTargetRplID = rplComp.Id();
		}

		S7R_BaseMenuAction action = menuManager.FindAction(m_sExecutedActionName);
		if (action)
		{
			DeleteShownAction();
			action.VisualizeAction(targetPosition);
		}

		Rpc(RPC_RequestExecuteAction, actionIndex, cursorTargetRplID, targetPosition, playerID);
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionIndex
	//! \param[in] cursorTargetID
	//! \param[in] targetPosition
	//! \param[in] playerID
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void RPC_RequestExecuteAction(int actionIndex, RplId cursorTargetID, vector targetPosition, int playerID)
	{
		S7R_MenuManagerComponent menuManager = S7R_MenuManagerComponent.GetInstance();
		if (!menuManager)
			return;
		
		//generate random seed for voiceline
		float soundEventSeed = Math.RandomFloatInclusive(0, 1);
		menuManager.RequestActionExecution(actionIndex, cursorTargetID, targetPosition, playerID, soundEventSeed);
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionIndex
	void ActionExecutedCallback(int actionIndex)
	{
		Rpc(RPC_ActionExecutedCallback, actionIndex);
	}

	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionIndex
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	void RPC_ActionExecutedCallback(int actionIndex)
	{
		PlayActiondGesture(actionIndex);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Update functions
	//------------------------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] owner
	//! \param[in] isOpen
	void UpdateRadialMenu(IEntity owner, bool isOpen)
	{
		if (!m_RadialMenu || !m_Menu7RConfig || !isOpen)
			return;

		PlayerCamera camera = PlayerCamera.Cast(GetGame().GetCameraManager().CurrentCamera());
		if (!camera)
			return;

		m_SelectedEntity = camera.GetCursorTarget();

		S7R_Player7RMenuCategoryElement rootCategory = m_Menu7RConfig.GetRootCategory();
		if (!rootCategory)
			return;

		AddElementsFromCategory(rootCategory);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Physics Helpers
	//------------------------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------------------------
	//! Perform a TraceSegmented starting from Camera position in camera look direction with givin lengh
	//! \param[in] float, range in meters
	protected void PhysicsActionTrace(float range = ACTION_VISUAL_RANGE)
	{
		PlayerController controller = GetGame().GetPlayerController();
		PlayerCamera camera = PlayerCamera.Cast(GetGame().GetCameraManager().CurrentCamera());
		if (!camera)
			return;

		IEntity controlledEntity = controller.GetControlledEntity();

		vector mat[4];
		camera.GetTransform(mat);
		vector end = mat[3] + mat[2] * range;
		array<IEntity> excludeArray = {};
		excludeArray.Insert(controlledEntity);

		ChimeraCharacter playerCharacter = ChimeraCharacter.Cast(controlledEntity);		
		if (playerCharacter && playerCharacter.IsInVehicle())
		{
			CompartmentAccessComponent compartmentComp = playerCharacter.GetCompartmentAccessComponent();
			if (compartmentComp)
			{
				IEntity vehicleIn = compartmentComp.GetVehicleIn(playerCharacter);
				if (vehicleIn)
					excludeArray.Insert(vehicleIn);
			}
		}

		m_PhysicsHelper = new SCR_PhysicsHelper();
		m_PhysicsHelper.TraceSegmented(mat[3], end, TraceFlags.ENTS | TraceFlags.WORLD | TraceFlags.ANY_CONTACT, EPhysicsLayerDefs.Projectile, excludeArray);
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionIndex
	void PlayActiondGesture(int actionIndex)
	{
		if (actionIndex <= 0)
			return;

		SCR_MapEntity mapEntity = SCR_MapEntity.GetMapInstance();

		//skip the action gesture if player has map open
		if (mapEntity && mapEntity.IsOpen())
			return;

		S7R_BaseMenuAction action = S7R_BaseMenuAction.Cast(m_MenuManager.FindAction(m_MenuManager.FindActionNameFromIndex(actionIndex)));
		if (!action)
			return;

		int gestureID = action.GetActionGestureID();

		IEntity playerControlledEntity = GetGame().GetPlayerController().GetControlledEntity();

		if (!playerControlledEntity)
			return;

		SCR_CharacterControllerComponent characterComponent = SCR_CharacterControllerComponent.Cast(playerControlledEntity.FindComponent(SCR_CharacterControllerComponent));
		if (!characterComponent)
			return;

		if (characterComponent.IsWeaponADS())
			return;

		characterComponent.TryStartCharacterGesture(gestureID, 3000);
	}
}
