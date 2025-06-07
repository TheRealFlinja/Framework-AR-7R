[EntityEditorProps(category: "Framework7R/Entities/LoadoutComponent", description: "7R Container component")]
class S7R_LoadoutUserActionsComponentClass: ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------


/*
class S7R_LoadoutUserActionsComponent: ScriptComponent
{
	protected ref array<ref ScriptedUserAction> m_loadoutUserActions;
	protected ref ActionsManagerComponent m_actionManagerCmp;
	
	protected ref SCR_LoadoutManager m_loadoutManager;
	
	protected void AddLoadouts()
	{
		if(!m_actionManagerCmp)
		{
			Print("[S7R_SpawnVehicleAction: AddLoadouts] No ActionsManagerComponent found", LogLevel.WARNING);
			return;
		}
		
		
		foreach (ScriptedUserAction userAction : m_loadoutUserActions)
		{
			
		}
		
		m_actionManagerCmp.AddUserActionEventListener();
	}
	
	protected void OnPostInit(IEntity owner)
	{
		if (!GetGame().InPlayMode())
			return;
		
		m_actionManagerCmp = ActionsManagerComponent.Cast(owner.FindComponent(ActionsManagerComponent));
		
		if (!m_actionManagerCmp)
		{
			Print("[S7R_SpawnVehicleAction: OnPostInit] No ActionsManagerComponent found", LogLevel.WARNING);
			return;
		}
		
		GetGame().GetCallqueue().CallLater(AddLoadouts);
	}
}

*/
