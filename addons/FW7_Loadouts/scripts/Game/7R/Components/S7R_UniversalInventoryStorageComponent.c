modded class SCR_UniversalInventoryStorageComponent
{
	//------------------------------------------------------------------------------------------------
	override bool CanStoreItem(IEntity item, int slotID)
	{
		InventoryItemComponent pItemComp = GetItemComponent(item);
		if (!pItemComp)
			return false;

		bool bWeightOK = IsAdditionalWeightOk(pItemComp.GetTotalWeight());
		if (!bWeightOK)
		{
			if (pInventoryManager)	
				pInventoryManager.SetReturnCode(EInventoryRetCode.RETCODE_ITEM_TOO_HEAVY);
			
			return false;
		}

		IEntity parent = GetOwner().GetParent();
		if (parent)
		{
			if (parent == item.GetParent())
				return true; // If transfered from my parent inventory to me then it has to be within parents allowed weight limit

			return CheckParentWeightLimit(pItemComp.GetTotalWeight());
		}

		return true;
	}
}
