[BaseContainerProps("", "Entry of one action"), S7R_BaseGroupActionTitleField("m_sActionName")]
class S7R_BaseMenuAction
{
	[Attribute("", UIWidgets.EditBox, "Unique name of the action")]
	protected string m_sActionName;
	
	[Attribute("", UIWidgets.EditBox, "Display name of the action, in future will replace the one in commanding menu conf")]
	protected string m_sActionDisplayName;
	
	[Attribute(defvalue: "0", desc: "ID of the gesture in gesture state machine to be played when action is given out. 0 = no gesture")]
	protected int m_iGestureID;
	
	[Attribute("{2EFEA2AF1F38E7F0}UI/Textures/Icons/icons_wrapperUI-64.imageset", UIWidgets.ResourceNamePicker, "Imageset source for display icon" )]
	protected ResourceName m_sImageset;
	
	[Attribute("", UIWidgets.EditBox, "Name of the icon associated to the action, taken from appropriate imageset set in the radial menu" )]
	protected string m_sIconName;
	
	[Attribute(defvalue: "0", desc: "Will the action show preview in world before it is given out")]
	protected bool m_bShowPreview;

	[Attribute(SCR_ECharacterRank.INVALID.ToString(), UIWidgets.ComboBox, desc: "Rank that is requried in order to use this action.\nINVALID == no requirement", enums: ParamEnumArray.FromEnum(SCR_ECharacterRank))]
	protected SCR_ECharacterRank m_eRequiredRank;

	protected LocalizedString m_sCannotPerformReason;

	protected static const LocalizedString CANNOT_PERFORM_RANK_TOO_LOW = "#AR-SCR_CannotPefrorm_RankTooLow";
	//------------------------------------------------------------------------------------------------
	//! method that will be executed when the action is selected in the menu
	//! This method is right now broadcasted to all clients, so if the action 
	//! is intended only for specific clients, it needs to be filtered inside 
	// Returns true if the action was executed succesfully, false otherwise.
	bool Execute(IEntity cursorTarget, IEntity target, vector targetPosition, int playerID, bool isClient)
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	void VisualizeAction(vector targetPosition);
	
	//------------------------------------------------------------------------------------------------
	void VisualizeActionPreview(vector targetPosition);
	
	//------------------------------------------------------------------------------------------------
	//!
	string GetIconName()
	{
		return m_sIconName;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	string GetActionDisplayName()
	{
		return m_sActionDisplayName;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	ResourceName GetIconImageset()
	{
		return m_sImageset;
	}
		
	//------------------------------------------------------------------------------------------------
	//!
	string GetActionName()
	{
		return m_sActionName;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	int GetActionGestureID()
	{
		return m_iGestureID;
	}
	
	//------------------------------------------------------------------------------------------------
	bool CanShowPreview()
	{
		return m_bShowPreview;
	}
			
	//------------------------------------------------------------------------------------------------
	//!
	bool CanRoleShow()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	bool CanBeShownInCurrentLifeState()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	bool CanBeShown()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	bool CanShowOnMap()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	//!
	bool CanBePerformed(notnull SCR_ChimeraCharacter user)
	{
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

	//------------------------------------------------------------------------------------------------
	protected void SetCannotPerformReason(LocalizedString newReason)
	{
		m_sCannotPerformReason = newReason;
	}

	//------------------------------------------------------------------------------------------------
	LocalizedString GetCannotPerformReason()
	{
		return m_sCannotPerformReason;
	}
}