/*
 * CSeedItem.cpp
 *
 *  Created on: 11.03.2012
 *      Author: Tim
 */

#include "Items/SeedItem.h"

eItemType CSeedItem::GetType()
{
	return IT_SEED;
}

bool CSeedItem::RequiresDirection()
{
	return true;
}

void CSeedItem::OnUse(CVector UsePos, CEntity* pUser, CMap* pMap)
{
	if(pMap->GetTile(UsePos) == CMapTile::FarmTile) {
		if(pMap->GetTileData(UsePos).Is_Set(FTD_FULLY_GROWN))
			pMap->GetTile(UsePos)->OnInteract(UsePos, pMap, pUser);

		pMap->GetTileData(UsePos).Unset(FTD_FULLY_GROWN);

		pMap->GetTileData(UsePos).Unset(FT_GrowTimeMask);
		pMap->GetTileData(UsePos).Set(5);

		pMap->GetTileData(UsePos).Unset(FT_PlantTypeMask);
		pMap->GetTileData(UsePos).Set(((CSeedType*)CItemTypeList::GetType(TypeId))->SeedType);

		CUseableItem::OnUse(UsePos, pUser, pMap);
	} else gMessages.AddMessage("Du kannst Samen nur auf Farm-Feldern pflanzen");

}

