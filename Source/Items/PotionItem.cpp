/*
 * PotionItem.cpp
 *
 *  Created on: 18.03.2012
 *      Author: Tim
 */

#include "Items/PotionItem.h"

const char* CPotionItem::GetName()
{
	return "Heiltrank";
}

const char* CPotionItem::GetDescription()
{
	return "Ein Trank mit heilender Wirkung";
}

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
	pUser->GetHealed(4);
	CItem::OnUse(UsePos, pUser, pMap);
}

