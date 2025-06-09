[EntityEditorProps(category: "GameScripted/Actioning", description: "Actioning manager, attach to game mode entity!.")]
class S7R_MenuManagerComponentClass : SCR_BaseGameModeComponentClass
{
}

//------------------------------------------------------------------------------------------------
class S7R_MenuManagerComponent : SCR_BaseGameModeComponent
{	
	[Attribute("{48DB05FBC10E600B}Configs/Menu7R/Actions7R.conf")]
	protected ResourceName m_sActionsConfigPath;
	
	protected S7R_PlayerActionsConfig m_ActionsConfig;
	
	protected static S7R_MenuManagerComponent s_Instance;
	
	protected ref array<ref S7R_BaseMenuAction> m_aActions;
	protected ref map<string, ref S7R_BaseMenuAction> m_mNameAction = new map<string, ref S7R_BaseMenuAction>();

	protected static const int NORMAL_PRIORITY = 50;
	
	//------------------------------------------------------------------------------------------------
	//! \return
	static S7R_MenuManagerComponent GetInstance()
	{
		return s_Instance;
	}
	
	//------------------------------------------------------------------------------------------------
	// constructor
	//! \param[in] src
	//! \param[in] ent
	//! \param[in] parent
	void S7R_MenuManagerComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		if (!s_Instance)
			s_Instance = this;
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		
		InitiateActionMaps();
		
		SCR_BaseGameMode gameMode = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		if (!gameMode)
			return;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	void InitiateActionMaps()
	{
		S7R_PlayerActionsConfig actionsConfig = GetActionsConfig();
		if (!actionsConfig)
			return;
		
		m_aActions = actionsConfig.GetActions();
		
		foreach (S7R_BaseMenuAction action : m_aActions)
		{
			m_mNameAction.Insert(action.GetActionName(), action);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//! Called on server
	//! \param[in] actionIndex
	//! \param[in] cursorTargetID
	//! \param[in] targetPosition
	//! \param[in] playerID
	void RequestActionExecution(int actionIndex, RplId cursorTargetID, vector targetPosition, int playerID, float seed)
	{
		//find entity of AI that will be responding to actions
		S7R_BaseMenuAction action = S7R_BaseMenuAction.Cast(FindAction(FindActionNameFromIndex(actionIndex)));
		RplId responderRplId;
		
		//check if the passed arguments are valid, if yes, send a callback RPC to actioners playercontroller so he can make a gesture.			
		RPC_DoExecuteAction(actionIndex, cursorTargetID, responderRplId, targetPosition, playerID, seed);
		Rpc(RPC_DoExecuteAction, actionIndex, cursorTargetID, responderRplId, targetPosition, playerID, seed);
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionIndex
	//! \param[in] cursorTargetID
	//! \param[in] targetPosition
	//! \param[in] playerID
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	void RPC_DoExecuteAction(int actionIndex, RplId cursorTargetID, RplId responderRplID, vector targetPosition, int playerID, float seed)
	{
		RplComponent rplComp;
		IEntity cursorTarget, group;
		rplComp = RplComponent.Cast(Replication.FindItem(cursorTargetID));
		if (rplComp)
			cursorTarget = rplComp.GetEntity();
		
		rplComp = RplComponent.Cast(GetOwner().FindComponent(RplComponent));
		if (rplComp)
		{
			S7R_BaseMenuAction action = FindAction(FindActionNameFromIndex(actionIndex));
			if (action.Execute(cursorTarget, group, targetPosition, playerID, rplComp.IsProxy()))
			{
				if (!rplComp.IsMaster())
					return;
				
				PlayerController controller = GetGame().GetPlayerManager().GetPlayerController(playerID);
				if (!controller)
					return;
				
				S7R_MenuPlayerComponent actioningComp = S7R_MenuPlayerComponent.Cast(controller.FindComponent(S7R_MenuPlayerComponent));
				if (!actioningComp)
					return;
				
				actioningComp.ActionExecutedCallback(actionIndex);			
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionName
	//! \return
	S7R_BaseMenuAction FindAction(string actionName)
	{
		return m_mNameAction.Get(actionName);
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionName
	//! \return
	int FindActionIndex(string actionName)
	{
		S7R_BaseMenuAction action = FindAction(actionName);
		if (!action)
			return -1;
		
		return m_aActions.Find(action);
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionIndex
	//! \return
	string FindActionNameFromIndex(int actionIndex)
	{
		S7R_BaseMenuAction action = m_aActions.Get(actionIndex);
		if (!action)
			return string.Empty;
		
		return action.GetActionName();
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionName
	//! \return
	bool CanShowAction(string actionName)
	{
		S7R_BaseMenuAction action = FindAction(actionName);
		if (!action)
			return false;
		
		return action.CanBeShown();
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] actionName
	//! \return
	bool CanShowOnMap(string actionName)
	{
		S7R_BaseMenuAction action = FindAction(actionName);
		if (!action)
			return false;
		
		return action.CanShowOnMap();
	}
	
	//------------------------------------------------------------------------------------------------
	//! \return
	S7R_PlayerActionsConfig GetActionsConfig()
	{
		if (m_ActionsConfig)
			return m_ActionsConfig;
		
		Resource holder = BaseContainerTools.LoadContainer(m_sActionsConfigPath);
		if (!holder)
			return null;
		
		BaseContainer container = holder.GetResource().ToBaseContainer();
		if (!container)
			return null;
		
		S7R_PlayerActionsConfig actionsConfig = S7R_PlayerActionsConfig.Cast(BaseContainerTools.CreateInstanceFromContainer(container));
		if (!actionsConfig)
			return null;
		
		m_ActionsConfig = actionsConfig;
		return m_ActionsConfig;
	}
	
	//------------------------------------------------------------------------------------------------
	//! \return
	string GetActionDisplayTextByName(string actionName)
	{
		S7R_BaseMenuAction action = FindAction(actionName);
		if (!action)
			return string.Empty;
		
		return action.GetActionDisplayName();
	}
}
