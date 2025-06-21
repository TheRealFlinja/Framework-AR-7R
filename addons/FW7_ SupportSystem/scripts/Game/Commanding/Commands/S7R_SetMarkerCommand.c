[BaseContainerProps("7R/Commands", "Set Marker"), SCR_BaseGroupCommandTitleField("m_sCommandName")]
class S7R_SetMarkerCommand: SCR_BaseGroupCommand
{
	[Attribute("", uiwidget: UIWidgets.ComboBox, enumType: ESupportMarkerType)]
	protected ESupportMarkerType m_eMarkerType;
	
	protected S7R_SupportSystemManagerComponent m_supportSystemManager;
	protected S7R_ResourceHandlerComponent m_ResourceHandler;
	
	//------------------------------------------------------------------------------------------------
	override bool Execute(IEntity cursorTarget, IEntity target, vector targetPosition, int playerID, bool isClient)
	{		
		if (!m_ResourceHandler || !m_supportSystemManager)
		{
			Print("[S7R_SetMarkerCommand: OnPerform] Failed to init", LogLevel.ERROR);
			return false;
		}
		
		m_supportSystemManager.RegisterMarker(targetPosition, m_eMarkerType);
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	// void VisualizeAction(vector targetPosition);
	
	//------------------------------------------------------------------------------------------------
	// void VisualizeActionPreview(vector targetPosition);
	
	//------------------------------------------------------------------------------------------------
	//!
	override bool CanBeShown()
	{
		m_ResourceHandler = S7R_ResourceHandlerComponent.GetInstance();
		m_supportSystemManager = S7R_SupportSystemManagerComponent.GetInstance();
		
		if (!m_ResourceHandler || !m_supportSystemManager)
		{
			return false;
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	override bool CanShowOnMap()
	{
		return true;
	}
}