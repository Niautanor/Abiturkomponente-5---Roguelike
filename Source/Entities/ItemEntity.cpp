/*
 * ItemEntity.cpp
 *
 *  Created on: 05.02.2012
 *      Author: Tim
 */

#include "Entities/ItemEntity.h"

CItemEntity::CItemEntity(CItem* pItem, CVector Position)
{
	char Entity_c;
	CColor Fg = CColor(255,255,255), Bg = CColor(0,0,0);
	switch(pItem->GetType()) {
	case IT_NO_ITEM:
		Entity_c = '?';
		Bg = CColor(255, 0, 255);
		break;
	case IT_WEAPON:
		Entity_c = '/';
		Fg = CColor(255, 0, 0);
		break;
	case IT_SEED:
		Entity_c = ':';
		Fg = CColor(20, 230, 20);
		break;
	default:
		Entity_c = ' ';
		break;
	}

	default_tile = Tile(Entity_c, Fg, Bg);

	Pos = Position;

	SetItemType(pItem->GetType());
	SetExtraData(pItem->ExtraData);
}

const char* CItemEntity::GetName()
{
	switch(GetItemType()) {
	case IT_NO_ITEM:
		return "Mysterious Blob";
	case IT_WEAPON:
		return "Waffe";
	case IT_SEED:
		return "Samen";
	default:
		return "Generic Item Text";
	}
}

const char* CItemEntity::GetDescription()
{
	//TODO: GetName auf GetDescription Anwenden
	return "Item-Entity-Beschreibung";
}

eItemType CItemEntity::GetItemType()
{
	return (eItemType)((EntityFlags.raw() & 0xFE/*0xFE ist der Typspezifische Teil von EntityFlags*/) >> 1);
}

void CItemEntity::SetItemType(eItemType Type)
{
	EntityFlags.Set(Type << 1);
}

Uint8 CItemEntity::GetExtraData(CMap *pMap)
{
	return ItemExtraData;
}

void CItemEntity::SetExtraData(Uint8 ExtraData)
{
	ItemExtraData = ExtraData;
}









