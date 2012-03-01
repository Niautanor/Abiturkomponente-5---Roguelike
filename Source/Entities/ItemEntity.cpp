/*
 * ItemEntity.cpp
 *
 *  Created on: 05.02.2012
 *      Author: Tim
 */

#include "../../Include/Entities/ItemEntity.h"

CItemEntity::CItemEntity(CItem* pItem, CVector Position)
{
	char Entity_c;
	CColor Fg = CColor(255,255,255), Bg = CColor(0,0,0);
	switch(pItem->Type) {
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

	SetItemType(pItem->Type);
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
	return IT_SEED;
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









