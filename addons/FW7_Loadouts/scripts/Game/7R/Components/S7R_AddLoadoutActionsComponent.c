/*

TO DO:

	Find a way to initialise userActions and add them automatically

*/

/*
[EntityEditorProps(category: "7R/Component", description: "Insert actions for the loadouts")]
class S7R_AddLoadoutActionsComponentClass : ScriptComponentClass
{
}


class S7R_AddLoadoutActionsComponent : ScriptComponent
{
	[Attribute("1", UIWidgets.Auto, category: "Loadouts", enumType: ERoleTypes7R)]
	protected ERoleTypes7R m_eLoadoutTypes;
	
	[Attribute("Alpha", UIWidgets.Auto, category: "Loadouts", params: "Alpha Bravo Charlie Delta", desc: "Only needed for specific squads with different loadouts")]
	protected string m_sSquad;
	
	[Attribute("", UIWidgets.Auto, category: "Context", desc: "Link the ActionContext here")]
	protected string m_sActionContextName;
	
	protected ActionsManagerComponent m_ActionManager;
	protected SCR_LoadoutManager m_LoadoutManager;
	
	override protected void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		
		// Get managers
		m_ActionManager = ActionsManagerComponent.Cast(owner.FindComponent(ActionsManagerComponent));
		m_LoadoutManager = GetGame().GetLoadoutManager();
		
		if (!m_ActionManager || !m_LoadoutManager)
		{
			Print("[S7R_AddLoadoutActionsComponent: OnPostInit] Configuration failed", LogLevel.ERROR);
			return;
		}
		
		// Get context
		UserActionContext context = m_ActionManager.GetContext(m_sActionContextName);
		
		if (!context)
		{
			Print("[S7R_AddLoadoutActionsComponent: OnPostInit] No contexts with the selected name found", LogLevel.ERROR);
			return;
		}
		
		// Register useractions and eventlisteners
		
	}
	
	void LoadoutEventListener(IEntity user, ScriptedUserAction action, EUserActionEvent e)
	{
		switch (e)
		{
			case EUserActionEvent.StartAction:
				Print("[S7R_AddLoadoutActionsComponent: LoadoutEventListener] Configuration failed", LogLevel.NORMAL);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//! Adds a user action to the manager and optionally registers an event listener
    void AddUserActions()
    {
        if (!m_ActionManager || !m_LoadoutManager)
            return;
		
		foreach (ERoleTypes7R role: g_aERoleTypes7R)
    }

	//------------------------------------------------------------------------------------------------
	//! Adds a user action to the manager and optionally registers an event listener
    void AddUserAction(ScriptedUserAction action)
    {
        if (!m_ActionManager || !action)
            return;
		
        // Optionally add an event listener
		//m_ActionManager.AddUserActionEventListener(action, listener);
		
		//proto bool AddUserActionEventListener(ScriptedUserAction action, UserActionEventListener listener);
    }
}
