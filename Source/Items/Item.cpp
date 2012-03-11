/*
 * Item.cpp
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#include "Items/Item.h"

CItem::CItem(eItemExtraData ED, Uint8 Start_Uses) {
	ExtraData = ED;
	Uses = Start_Uses;
}

CItem::~CItem() {
}

CItem* CItem::GenerateObject(Uint8 Type)
{
	switch(Type) {
	case IT_NO_ITEM:
		return NULL;
	case IT_SEED:
		return new CSeedItem(SIED_PLUMPHELMET);
	case IT_WEAPON:
		return new CWeaponItem(IED_NONE, 5);
	default:
		return NULL;
	}
}

eItemType CItem::GetType()
{
	return IT_NO_ITEM;
}

void CItem::OnUse(CVector UsePos, CEntity *pUser, CMap *pMap)
{
}



