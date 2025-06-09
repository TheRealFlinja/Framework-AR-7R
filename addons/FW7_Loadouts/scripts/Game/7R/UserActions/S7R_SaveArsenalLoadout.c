[BaseContainerProps(description: "7R Save Current Loadout Action", configRoot: true)]
modded class SCR_SaveArsenalLoadout : SCR_BaseFactionCheckUserAction
{
	[Attribute("Loadout7R", desc: "")]
	protected string m_sS7RSlotId;

	[Attribute("Loadout 1", desc: "")]
	protected string m_sS7RLoadoutLabel;

	protected RplComponent m_S7RRplComp;
	
	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		super.Init(pOwnerEntity, pManagerComponent);
		m_S7RRplComp = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	override protected void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (!m_ArsenalManager || !m_ArsenalComponent || !m_S7RRplComp || m_S7RRplComp.IsProxy())
			return;

		const int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		if (playerId <= 0)
			return;
		
		PlayActionSoundEffect(pOwnerEntity);

		m_ArsenalManager.S7R_TrySavePlayerArsenalLoadout_S(m_sS7RSlotId, playerId, GameEntity.Cast(pUserEntity), m_ArsenalComponent, SCR_EArsenalSupplyCostType.DEFAULT);
	}

	//------------------------------------------------------------------------------------------------
	override protected void UpdateActionDisplayName(notnull IEntity user)
	{
		//~ There is no arsenal component
		if (!m_ArsenalComponent)
			return;

		//~ Makes sure it is only updated when needed
		SCR_EArsenalSaveType arsenalSaveType = m_ArsenalComponent.GetArsenalSaveType();

		//~ There is no arsenal manager
		if (!m_ArsenalManager)
			return;

		//~ Get the arseal save type holder
		SCR_ArsenalSaveTypeInfoHolder saveTypesHolder = m_ArsenalManager.GetArsenalSaveTypeInfoHolder();
		if (!saveTypesHolder)
			return;

		//~ Get the save type UIinfo of the current arsenal save type
		SCR_ArsenalSaveTypeUIInfo saveTypeUIInfo = saveTypesHolder.GetUIInfoOfType(arsenalSaveType);
		if (!saveTypeUIInfo)
		{
			m_sSaveTypeDisplayName = string.Empty;
			return;
		}

		//~ Get Action display name
		m_sSaveTypeDisplayName = string.Format("Save loadout - %1", m_sS7RLoadoutLabel);

		//~ No custom display name for the action so use default
		if (SCR_StringHelper.IsEmptyOrWhiteSpace(m_sSaveTypeDisplayName))
		{
			SetCannotPerformReason(string.Empty);
			return;
		}

		//~ Action is disabled so show the action name in disabled () and use default
		if (arsenalSaveType == SCR_EArsenalSaveType.SAVING_DISABLED)
		{
			SetCannotPerformReason(m_sSaveTypeDisplayName);
			m_sSaveTypeDisplayName = string.Empty;
			return;
		}
	}
}
