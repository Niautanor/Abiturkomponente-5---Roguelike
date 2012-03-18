/*
 * CSeedItem.cpp
 *
 *  Created on: 11.03.2012
 *      Author: Tim
 */

#include "Items/SeedItem.h"

const char* CSeedItem::GetName()
{
	return "Samen";
}

const char* CSeedItem::GetDescription()
{
	return "Das ist ein Samen, den du in den Boden stecken kannst";
}

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
		pMap->GetTileData(UsePos).Unset(FTD_FULLY_GROWN);

		pMap->GetTileData(UsePos).Unset(FT_GrowTimeMask);
		pMap->GetTileData(UsePos).Set(5);

		pMap->GetTileData(UsePos).Unset(FT_PlantTypeMask);
		pMap->GetTileData(UsePos).Set(ExtraData);

		CItem::OnUse(UsePos, pUser, pMap);
	} else gMessages.AddMessage("Du kannst Samen nur auf Farm-Feldern pflanzen");

}

