/*
 * Item.cpp
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#include "Items/Item.h"

CItem::CItem(eItemTypeList ItemTypeId) {
	TypeId = ItemTypeId;
}

CItem::~CItem() {
}

CItem* CItem::GenerateObject(Uint8 Type)
{
	switch(Type) {
	case IT_NO_ITEM:
		return NULL;
	case IT_SEED:
		return new CSeedItem(ITL_PLUMPHELMET_SEED);
	case IT_WEAPON:
		return new CWeaponItem(ITL_SHARP_SWORD_WEAPON);
	case IT_POTION:
		return new CPotionItem(ITL_SMALL_POTION);
	default:
		return NULL;
	}
}

const char* CItem::GetName()
{
	return CItemTypeList::GetType(TypeId)->Name.c_str();
}

const char* CItem::GetDescription()
{
	return CItemTypeList::GetType(TypeId)->Description.c_str();
}

eItemType CItem::GetType()
{
	return IT_NO_ITEM;
}

bool CItem::IsUseable()
{
	return CItemTypeList::GetType(TypeId)->IsUsable();
}

bool CItem::RequiresDirection()
{
	return false;
}

void CItem::OnUse(CVector UsePos, CEntity *pUser, CMap *pMap)
{
}



