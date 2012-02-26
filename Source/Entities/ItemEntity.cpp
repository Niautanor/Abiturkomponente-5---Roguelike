/*
 * ItemEntity.cpp
 *
 *  Created on: 05.02.2012
 *      Author: Tim
 */

#include "../../Include/Entities/ItemEntity.h"

const char* CItemEntity::GetName()
{
	return "Item-Entity-Name";
}

const char* CItemEntity::GetDescription()
{
	return "Item-Entity-Beschreibung";
}

eItemType CItemEntity::GetItemType(CMap *pMap)
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









