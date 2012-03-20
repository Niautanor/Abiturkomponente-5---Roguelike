/*
 * PotionItem.cpp
 *
 *  Created on: 18.03.2012
 *      Author: Tim
 */

#include "Items/PotionItem.h"

eItemType CPotionItem::GetType()
{
	return IT_POTION;
}

bool CPotionItem::RequiresDirection()
{
	return false;
}

void CPotionItem::OnUse(CVector UsePos, CEntity* pUser, CMap* pMap)
{
	pUser->GetHealed(((CPotionType*)CItemTypeList::GetType(TypeId))->Heal);
	CUseableItem::OnUse(UsePos, pUser, pMap);
}

