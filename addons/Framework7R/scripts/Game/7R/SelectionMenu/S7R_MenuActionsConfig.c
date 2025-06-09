//! Actions config root
[BaseContainerProps(configRoot: true)]
class S7R_PlayerActionsConfig : Managed
{
	[Attribute("", UIWidgets.Object, "Available actions")]
	protected ref array<ref S7R_BaseMenuAction> m_aActions;
	
	array<ref S7R_BaseMenuAction> GetActions()
	{
		return m_aActions;
	}
};

//! 7R menu config root
[BaseContainerProps(configRoot: true)]
class S7R_Player7RMenuConfig : Managed
{
	[Attribute(desc: "7R configs and actions pairs")]
	protected ref S7R_Player7RMenuCategoryElement m_RootCategory;
	
	S7R_Player7RMenuCategoryElement GetRootCategory()
	{
		return m_RootCategory;
	}
};

//! 7R menus config to setup different menus to different keybinds
[BaseContainerProps(configRoot: true)]
class S7R_Player7RMenuActionsSetup : Managed
{
	[Attribute("", UIWidgets.Object, "7R configs and actions pairs")]
	ref array<ref S7R_Player7RConfigActionPair> m_aActionConfigPairs;
};

[BaseContainerProps()]
class S7R_Player7RConfigActionPair : Managed
{
	[Attribute("", UIWidgets.EditBox, "Name of the action in ChimeraInputCommon.conf that triggers menu with selected config" )]
	protected string m_sActionName;
	
	[Attribute()]
	protected ResourceName m_s7RMenuConf;
	
	//------------------------------------------------------------------------------------------------
	string GetActionName()
	{
		return m_sActionName;
	}
	
	//------------------------------------------------------------------------------------------------
	ResourceName GetConfig()
	{
		return m_s7RMenuConf;
	}
}

//! 7R menu action element class
[BaseContainerProps(), SCR_BaseContainerLocalizedTitleField("m_sActionName")]
class S7R_Player7RMenuAction : S7R_Player7RMenuBaseElement
{
	[Attribute("", UIWidgets.EditBox, "Name of the action used from S7R_PlayerActionsConfig" )]
	protected string m_sActionName;
	
	protected string m_sActionCustomDisplayText;
	
	//------------------------------------------------------------------------------------------------
	string GetActionName()
	{
		return m_sActionName;
	}
	
	//------------------------------------------------------------------------------------------------
	void SetActionName(string name)
	{
		m_sActionName = name;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetActionCustomName()
	{
		return m_sActionCustomDisplayText;
	}
	
	//------------------------------------------------------------------------------------------------
	void SetActionCustomName(string customName)
	{
		m_sActionCustomDisplayText = customName;
	}
};

//! 7R menu base element class
[BaseContainerProps()]
class S7R_Player7RMenuBaseElement : Managed
{

};

//! 7R menu base element class
[BaseContainerProps(), SCR_BaseContainerLocalizedTitleField("m_sCategoryDisplayText")]
class S7R_Player7RMenuCategoryElement : S7R_Player7RMenuBaseElement
{
	[Attribute("", UIWidgets.EditBox, "Name of the category that is displayed in the menu" )]
	protected string m_sCategoryDisplayText;
	
	[Attribute("", UIWidgets.Object, "Elements in the given category")]
	protected ref array<ref S7R_Player7RMenuBaseElement> m_aElements;
	
	[Attribute("", UIWidgets.ResourceNamePicker, "Imageset source from which icon will be selected. If this field is left empty then default icon will be used.")]
	protected ResourceName m_sImageset;

	[Attribute("", UIWidgets.EditBox, "Name of the icon associated to the category, taken from appropriate imageset set in the radial menu.\nIf this field is left empty then default icon will be used")]
	protected string m_sIconName;

	[Attribute()]
	protected bool m_bShowOnMap;
	
	//------------------------------------------------------------------------------------------------
	string GetCategoryDisplayText()
	{
		return m_sCategoryDisplayText;
	}

	//------------------------------------------------------------------------------------------------
	void SetCategoryDisplayText(string displayText)
	{
		m_sCategoryDisplayText = displayText;
	}	
	
	//------------------------------------------------------------------------------------------------
	array<ref S7R_Player7RMenuBaseElement> GetCategoryElements()
	{
		return m_aElements;
	}	
	
	//------------------------------------------------------------------------------------------------
	ResourceName GetIconImageset()
	{
		return m_sImageset;
	}

	//------------------------------------------------------------------------------------------------
	string GetIconName()
	{
		return m_sIconName;
	}

	//------------------------------------------------------------------------------------------------
	bool GetCanShowOnMap()
	{
		return m_bShowOnMap;
	}
};

class S7R_BaseGroupActionTitleField : BaseContainerCustomTitleField
{
	//------------------------------------------------------------------------------------------------
	override bool _WB_GetCustomTitle(BaseContainer source, out string title)
	{
		// Make sure variable exists
		int index = source.GetVarIndex("m_sActionName");
		if (index == -1)
			return false;

		// Tag string
		source.Get("m_sActionName", title);

		return true;
	}
}