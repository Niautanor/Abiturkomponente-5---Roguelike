/*
 * ItemEntity.cpp
 *
 *  Created on: 05.02.2012
 *      Author: Tim
 */

#include "Entities/ItemEntity.h"

void CItemEntity::InitFromItemData(eItemType Type, Uint8 ItemExtraData, CVector Position)
{
	char Entity_c;
	CColor Fg = CColor(255, 255, 255), Bg = CColor(0, 0, 0);
	switch(Type) {
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

	SetItemType(Type);
	SetExtraData(ItemExtraData);
}

CItemEntity::CItemEntity(CItem* pItem, CVector Position)
{
	InitFromItemData(pItem->GetType(), pItem->ExtraData, Position);
}

CItemEntity::CItemEntity(eItemType Type, Uint8 ItemExtraData, CVector Position)
{
	InitFromItemData(Type, ItemExtraData, Position);
}

const char* CItemEntity::GetName() const
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

const char* CItemEntity::GetDescription() const
{
	//TODO: GetName auf GetDescription Anwenden
	return "Item-Entity-Beschreibung";
}

eItemType CItemEntity::GetItemType() const
{
	return (eItemType) ((EntityFlags.raw() & 0xFE/*0xFE ist der Typspezifische Teil von EntityFlags*/) >> 1);
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

