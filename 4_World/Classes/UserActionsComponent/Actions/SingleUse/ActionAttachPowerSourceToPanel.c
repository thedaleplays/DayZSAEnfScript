class ActionAttachPowerSourceToPanel: ActionSingleUseBase
{
	void ActionAttachPowerSourceToPanel()
	{
		//m_MessageStartFail = "m_MessageStartFail";
		//m_MessageStart = "m_MessageStart";
		m_MessageSuccess = "I've attached the power source to the panel.";
		//m_MessageFail = "m_MessageFail";
		//m_MessageCancel = "m_MessageCancel";
	}

	override void CreateConditionComponents() 
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
	}
	
	override int GetType()
	{
		return AT_ATTACH_POWER_SOURCE_TO_PANEL;
	}
		
	override string GetText()
	{
		return "#attach_power_source";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		EntityAI target_entity = EntityAI.Cast( target.GetObject() );
		if ( player && target_entity && item )
		{			
			if ( target_entity.IsStaticTransmitter() && target_entity.GetInventory().AttachmentCount() == 0 )	//has any power source attachment attached
			{
				return true;
			}
		}
		
		return false;
	}

	override void OnCompleteServer( ActionData action_data )
	{
		EntityAI target_entity = EntityAI.Cast( action_data.m_Target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( action_data.m_MainItem );
		
		//find inventory location for attachment
		InventoryLocation target_location = new InventoryLocation;
		
		if( target_entity.GetInventory().FindFirstFreeLocationForNewEntity( item_entity.GetType(), FindInventoryLocationType.ATTACHMENT, target_location ) )
		{
			//target_entity.PredictiveTakeEntityToTargetAttachmentEx( target_entity, item_entity, target_location.GetSlot() );
			target_entity.LocalTakeEntityAsAttachmentEx( item_entity, target_location.GetSlot() );
		}
	}
	
	override void OnCompleteClient( ActionData action_data )
	{
		EntityAI target_entity = EntityAI.Cast( action_data.m_Target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( action_data.m_MainItem );
		
		//find inventory location for attachment
		InventoryLocation target_location = new InventoryLocation;
		
		if( target_entity.GetInventory().FindFirstFreeLocationForNewEntity( item_entity.GetType(), FindInventoryLocationType.ATTACHMENT, target_location ) )
		{
			//target_entity.PredictiveTakeEntityToTargetAttachmentEx( target_entity, item_entity, target_location.GetSlot() );
			target_entity.LocalTakeEntityAsAttachmentEx( item_entity, target_location.GetSlot() );
		}
	}
}