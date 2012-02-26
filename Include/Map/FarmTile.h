/*
 * CFarmTile.h
 *
 *  Created on: 04.02.2012
 *      Author: Tim
 */

#pragma once  /* CFARMTILE_H_ */

#include "Map/MapTile.h"

enum eFarmTileData {
	FTD_NO_PLANT = 0x00,
	FTD_FULLY_GROWN = 0x10,

	FTD_PLUMPHELMET = 0x20,
	FTD_SPINECRAWLER = 0x40,
	FTD_BANELING = 0x60,
	FTD_MOBSTERPLANT = 0x80,
	FTD_CANCER_CURE = 0xA0
};

const Uint8 FT_GrowTimeMask = 0x0F;
const Uint8 FT_PlantTypeMask = 0xE0;

#define FT_GROW_TIME(tile_data) (tile_data & FT_GrowTimeMask)
#define FT_PLANT_TYPE(tile_data) (tile_data & FT_PlantTypeMask)

class CFarmTile : public CMapTile
{
private:
public:
	CFarmTile(Tile T, MapTileFlag Flags) : CMapTile(T, Flags) { }

	//void OnInteract(CVector Pos, CMap* pMap, CEntity* pActor);//will never Happen <- Gets captured in Main_UserAction OnInteract
	void OnExamine(CVector Pos, CMap* pMap, CEntity* pActor);

	void Tick(CVector Pos, CMap* pMap);

	bool IsPassable(CVector Pos, CMap* pMap, CEntity* pTrespasser);
	Tile GetTile(CVector Pos, CMap* pMap);
};

