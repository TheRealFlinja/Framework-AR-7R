[BaseContainerProps("7R/Commands", "Set Marker"), SCR_BaseGroupCommandTitleField("m_sCommandName")]
class S7R_CallSupplyCommand: SCR_BaseGroupCommand
{
	[Attribute("", uiwidget: UIWidgets.ComboBox, enumType: ESupplyBoxType)]
	protected ESupplyBoxType m_eSupplyType;
	
	[Attribute("0", uiwidget: UIWidgets.Auto, enumType: ESupplyBoxType)]
	protected int m_iSupplyTypeID;
	
	[Attribute("0", uiwidget: UIWidgets.Auto, enumType: ESupplyBoxType)]
	protected int m_iAmount;
	
	protected S7R_SupportSystemManagerComponent m_supportSystemManager;
	protected S7R_ResourceHandlerComponent m_ResourceHandler;
	
	//------------------------------------------------------------------------------------------------
	override bool Execute(IEntity cursorTarget, IEntity target, vector targetPosition, int playerID, bool isClient)
	{		
		if (!m_ResourceHandler || !m_supportSystemManager)
		{
			Print("[S7R_CallSupplyCommand: Execute] Failed to init", LogLevel.ERROR);
			return false;
		}
		
		if (!m_supportSystemManager.CallSupplyDrop(m_iAmount, m_eSupplyType, m_iSupplyTypeID))
		{
			return false;
		}
		
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
	
	//------------------------------------------------------------------------------------------------
	//!
	override bool CanBePerformed(notnull SCR_ChimeraCharacter user)
	{
		if (!super.CanBePerformed(user))
			return false;
		
		string reason;
		if (!m_supportSystemManager.CanCallSupply(m_iAmount, m_eSupplyType, m_iSupplyTypeID, reason))
		{
			SetCannotPerformReason(reason);
			return false;
		}
		
		return true;
	}
}