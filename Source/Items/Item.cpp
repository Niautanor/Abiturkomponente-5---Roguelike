/*
 * Item.cpp
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#include "Items/Item.h"

CItem::CItem(eItemType T, eItemExtraData ED, Uint8 Start_Uses) {
	Type = T;
	ExtraData = ED;
	Uses = Start_Uses;
}

CItem::~CItem() {
}

void CItem::OnUse(CVector UsePos, CEntity *pUser, CMap *pMap)
{
	if(Type == IT_SEED) {
		if(pMap->GetTile(UsePos) == CMapTile::FarmTile) {
			pMap->GetTileData(UsePos).Unset(FTD_FULLY_GROWN);

			pMap->GetTileData(UsePos).Unset(FT_GrowTimeMask);
			pMap->GetTileData(UsePos).Set(5);

			pMap->GetTileData(UsePos).Unset(FT_PlantTypeMask);
			pMap->GetTileData(UsePos).Set(ExtraData);

			--Uses;
		} else gMessages.AddMessage("Du kannst Samen nur auf Farm-Feldern pflanzen");
	}
}



