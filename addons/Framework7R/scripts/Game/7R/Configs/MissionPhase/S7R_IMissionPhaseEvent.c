/*

TO DO:

	- Replace interface with Template Class if possble to avoid illegal use

*/


class IMissionPhaseEvent: ScriptAndConfig
{
	[Attribute("5", UIWidgets.Auto, category: "Parameters")]
	protected int m_iExecutionDelay;

	protected LocalizedString m_sSaveTypeDisplayName;
	
	//------------------------------------------------------------------------------------------------
	int GetSpawnDelay()
	{
		return m_iExecutionDelay;
	}
	
	//------------------------------------------------------------------------------------------------
	void UpdateToAbsoluteExecutionDelay(int updatedExecutionDelay)
	{
		m_iExecutionDelay = updatedExecutionDelay;
	}
	
	//------------------------------------------------------------------------------------------------
	void ExecuteEvent()
	{
		if (m_iExecutionDelay > 0)
		{
			GetGame().GetCallqueue().CallLater(RealExecuteEvent, m_iExecutionDelay*1000, false);
		}
		else
		{
			Print("[IMissionPhaseEvent] Delay is zero, this might cause some lag", LogLevel.WARNING);
			RealExecuteEvent();
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Abstract functions (not really but need something to override)
	protected void RealExecuteEvent()
	{
		Print("[IMissionPhaseEvent] ExecuteAction not implemented", LogLevel.ERROR);
	}
	
	//------------------------------------------------------------------------------------------------
	// Abstract functions (not really but need something to override)
	bool ValidateEvent()
	{
		Print("[IMissionPhaseEvent] ValidateEvent not implemented", LogLevel.ERROR);
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	bool GetActionNameScript(out string outName)
	{				
		if (!SCR_StringHelper.IsEmptyOrWhiteSpace(m_sSaveTypeDisplayName))
			outName = m_sSaveTypeDisplayName;
		
		return true;
	}
}
