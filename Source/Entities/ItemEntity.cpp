/*
 * ItemEntity.cpp
 *
 *  Created on: 05.02.2012
 *      Author: Tim
 */

#include "Entities/ItemEntity.h"

void CItemEntity::InitFromItemData(eItemType Type, eItemTypeList ItemTypeId, CVector Position)
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
		Fg = CL_RED;
		break;
	case IT_SEED:
		Entity_c = ':';
		Fg = CColor(20, 230, 20);
		break;
	case IT_POTION:
		Entity_c = '!';
		Fg = CL_RED;
		break;
	default:
		Entity_c = ' ';
		break;
	}

	default_tile = Tile(Entity_c, Fg, Bg);

	Pos = Position;

	SetItemType(Type);
	SetItemTypeId(ItemTypeId);
}

CItemEntity::CItemEntity(CItem* pItem, CVector Position)
{
	InitFromItemData(pItem->GetType(), pItem->TypeId, Position);
}

CItemEntity::CItemEntity(eItemType Type, eItemTypeList ItemTypeId, CVector Position)
{
	InitFromItemData(Type, ItemTypeId, Position);
}

const char* CItemEntity::GetName()
{
	return CItemTypeList::GetType(TypeId)->Name.c_str();
}

const char* CItemEntity::GetDescription()
{
	return CItemTypeList::GetType(TypeId)->Description.c_str();
}

eItemType CItemEntity::GetItemType()
{
	return (eItemType) ((EntityFlags.raw() & 0xFE/*0xFE ist der Typspezifische Teil von EntityFlags*/) >> 1);
}

void CItemEntity::SetItemType(eItemType Type)
{
	EntityFlags.Set(Type << 1);
}

eItemTypeList CItemEntity::GetItemTypeId(CMap *pMap)
{
	return TypeId;
}

void CItemEntity::SetItemTypeId(eItemTypeList ItemTypeId)
{
	TypeId = ItemTypeId;
}

