/*

TO DO:

	Add Hints for players? (Can also be done in the action but prefer to do it here)
	Check area for enemies and disable spawn

*/
[EntityEditorProps(category: "Framework7R/Entities/GameMode", description: "SCR_Gamemode7R Component for Handling reinsertion objects")]
class S7R_ReinsertionManagerComponentClass: ScriptComponentClass
{
}

class S7R_ReinsertionManagerComponent: ScriptComponent
{
	[Attribute(defvalue: "120")]
	protected int m_iRallyLifetime;
	
	protected ref map<string, IEntity> m_mFOBEntities = new map<string, IEntity>;
	protected IEntity m_RallyEntity;
	
	//------------------------------------------------------------------------------------------------
	bool GetFOB(int i, out string key, out IEntity fob)
	{
		if (m_mFOBEntities.Count() < i)
		{
			return false;
		}
		
		key = m_mFOBEntities.GetKey(i);
		if (!key)
			return false;
		
		fob = m_mFOBEntities.Get(key);
		if (!fob)
			return false;
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool RegisterFOB(string key, IEntity fob)
	{
		if (!fob || !key)
		{
			Print("[S7R_ReinsertionManagerComponent: RegisterFOB] Invalid FOB or key given", LogLevel.ERROR);
			return false;
		}
		
		if(!m_mFOBEntities.Contains(key))
		{
			Print("[S7R_ReinsertionManagerComponent: RegisterFOB] FOB with key already exists", LogLevel.ERROR);
			return false;
		}
		
		m_mFOBEntities.Set(key, fob);
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool UnregisterFOB(IEntity fob)
	{
	}
	
	//------------------------------------------------------------------------------------------------
	bool GetRally(out IEntity rally)
	{
		if (!m_RallyEntity)
		{
			return false;
		}
		
		rally = m_RallyEntity;
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool RegisterRally(IEntity rally)
	{
		if (m_RallyEntity)
		{
			Print("[S7R_ReinsertionManagerComponent: RegisterRally] Rally already present", LogLevel.WARNING);
			return false;
		}
		
		m_RallyEntity = rally;
		
		// Delete rally after lifetime
		GetGame().GetCallqueue().CallLater(UnregisterRally, m_iRallyLifetime*1000);
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool UnregisterRally()
	{
		if (!m_RallyEntity)
		{
			return true;
		}
		
		SCR_EntityHelper.DeleteEntityAndChildren(m_RallyEntity);
		
		// Check if deletion successfull
		if (!m_RallyEntity)
		{
			return true;
		} 
		else
		{
			return false;
		}
	}
	
	bool CanRegisterRally()
	{
		if (m_RallyEntity)
		{
			return false;
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool IsFOBSpawnPossible(int fobKey)
	{
		if (!m_mFOBEntities.GetKey(fobKey) || !m_mFOBEntities.GetElement(fobKey))
		{
			return false;
		}
		
		// Add enemy nearby check here
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool IsRallySpawnPossible(int fobKey)
	{
		if (!m_RallyEntity)
		{
			return false;
		}
		
		// Add enemy nearby check here
		return true;
	}
}
