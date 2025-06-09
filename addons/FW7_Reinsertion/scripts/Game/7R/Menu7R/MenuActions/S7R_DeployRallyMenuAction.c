[BaseContainerProps(), SCR_BaseGroupCommandTitleField("m_sActionName")]
class S7R_DeployRallyMenuAction: S7R_BaseMenuAction
{
	[Attribute(uiwidget: UIWidgets.ResourcePickerThumbnail)]
	protected ResourceName m_sRallyEntity;
	
	protected S7R_ReinsertionManagerComponent m_ReinsertionManager;
	protected S7R_ResourceHandlerComponent m_ResourceHandler;
	
	//------------------------------------------------------------------------------------------------
	override bool Execute(IEntity cursorTarget, IEntity target, vector targetPosition, int playerID, bool isClient)
	{		
		if (!m_ResourceHandler || !m_ReinsertionManager)
		{
			Print("[S7R_DeployRallyMenuAction: OnPerform] Failed to init", LogLevel.ERROR);
			return false;
		}
		
		SCR_ChimeraCharacter user = SCR_ChimeraCharacter.Cast(SCR_PlayerController.GetLocalControlledEntity());
		if (!user)
		{
			Print("[S7R_DeployRallyMenuAction: OnPerform] PlayerController not found", LogLevel.ERROR);
			return false;
		}
		
		IEntity rally;
		if (m_ReinsertionManager.CanRegisterRally())
			rally = m_ResourceHandler.SpawnEntityOnPosition(m_sRallyEntity, user.GetOrigin());
		
		if (!rally)
		{
			Print("[S7R_DeployRallyMenuAction: OnPerform] Failed to spawn rally", LogLevel.ERROR);
			return false;
		}
		
		if (!m_ReinsertionManager.RegisterRally(rally))
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
		m_ResourceHandler = S7R_ResourceHandlerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_ResourceHandlerComponent));
		m_ReinsertionManager = S7R_ReinsertionManagerComponent.Cast(GetGame().GetGameMode().FindComponent(S7R_ReinsertionManagerComponent));
		
		if (!m_ResourceHandler || !m_ReinsertionManager)
		{
			return false;
		}
		
		SCR_ChimeraCharacter user = SCR_ChimeraCharacter.Cast(SCR_PlayerController.GetLocalControlledEntity());
		if (!user)
		{
			return false;
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	override bool CanShowOnMap()
	{
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	override bool CanBePerformed(notnull SCR_ChimeraCharacter user)
	{
		if (!m_ReinsertionManager.CanRegisterRally())
		{
			SetCannotPerformReason("Rally already set");
			return false;
		}

		if (m_eRequiredRank == SCR_ECharacterRank.INVALID)
			return true;

		if (!SCR_XPHandlerComponent.IsXpSystemEnabled())
			return true;

		SCR_ECharacterRank currentRank = SCR_CharacterRankComponent.GetCharacterRank(user);
		if (currentRank < m_eRequiredRank)
		{
			SCR_Faction userFaction = SCR_Faction.Cast(user.GetFaction());
			if (!userFaction)
				return false;

			string requiredRankName = userFaction.GetRankName(m_eRequiredRank);
			string currentRankName = userFaction.GetRankName(currentRank);
			SetCannotPerformReason(SCR_StringHelper.Translate(CANNOT_PERFORM_RANK_TOO_LOW, requiredRankName, currentRankName));
			return false;
		}

		return true;
	}
}