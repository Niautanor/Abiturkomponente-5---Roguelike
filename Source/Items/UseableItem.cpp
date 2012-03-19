/*
 * UseableItem.cpp
 *
 *  Created on: 19.03.2012
 *      Author: Tim
 */

#include "Items/UseableItem.h"

CUseableItem::CUseableItem(eItemTypeList ItemTypeId) : CItem(ItemTypeId)
{
	Uses = ((CUseableType*)CItemTypeList::GetType(TypeId))->default_uses;
}

void CUseableItem::OnUse(CVector UsePos, CEntity* pUser, CMap* pMap)
{
	--Uses;
}
