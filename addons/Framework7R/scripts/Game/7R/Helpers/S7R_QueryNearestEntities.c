/*

TO DO:

	Test and add to scripts that require this
	Maybe add filter option (Only check for Character and Vehicle Entity)

*/

//------------------------------------------------------------------------------------------------
//! Class for querying the nearest entity within a sphere of radius searchDistanceM
class S7R_QueryNearestEntity
{
	protected vector m_vSearchPos;
	protected float m_fSearchDistanceM;
	protected float m_fShortestDistanceM;
	protected IEntity m_pNearestEntity;
	
	//------------------------------------------------------------------------------------------------
	//! Pass search radius in ctor
	void S7R_QueryNearestEntity(float searchDistance = 50)
	{
		m_fSearchDistanceM = searchDistance;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Store entity if it is the closest
	protected bool QueryCallback(IEntity entity)
	{
		float distance = vector.Distance(m_vSearchPos, entity.GetOrigin());
		
		if (m_fShortestDistanceM > distance)
		{
			m_fShortestDistanceM = distance;
			m_pNearestEntity = entity;
		}
		
		// Continue querying if distance didn't drop to zero
		return (m_fShortestDistanceM != 0);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Return nearest entity
	IEntity GetEntity(vector pos)
	{
		m_vSearchPos = pos;
		m_fShortestDistanceM = m_fSearchDistanceM;
		m_pNearestEntity = null;
		GetGame().GetWorld().QueryEntitiesBySphere(m_vSearchPos, m_fSearchDistanceM, QueryCallback);
		return m_pNearestEntity;
	}
}
