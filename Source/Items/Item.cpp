/*
 * Item.cpp
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#include "../../Include/Items/Item.h"

CItem::CItem() {
}

CItem::~CItem() {
}

void CItem::OnUse(CVector UsePos, CEntity *pUser, CMap *pMap)
{
	if(Type == IT_SEED) {
		if(pMap->GetTile(UsePos) == CMapTile::FarmTile) {

			pMap->GetTileData(UsePos).Unset(FT_PlantTypeMask);
			pMap->GetTileData(UsePos).Set(ExtraData);

		} else gMessages.AddMessage("Du kannst Samen nur auf Farm-Feldern pflanzen");
	}
}



