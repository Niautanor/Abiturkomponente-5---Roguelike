/*
 * FarmTile.cpp
 *
 *  Created on: 04.02.2012
 *      Author: Tim
 */

#include "Map/FarmTile.h"

void CFarmTile::Tick(CVector Pos, CMap *pMap)
{
	FlagSet<Uint8>& TileData = pMap->GetTileData(Pos);
	Uint8 GrowTime = FT_GROW_TIME(TileData.raw());
	//Uint8 PlantType = FT_PLANT_TYPE(TileData.raw());

	if(!TileData.Is_Set(FTD_FULLY_GROWN)) {
		if(GrowTime != 0) {
			GrowTime--;
			TileData.Unset(FT_GrowTimeMask);
			TileData.Set(GrowTime);
		}
		else TileData.Set(FTD_FULLY_GROWN);
	}
}

void CFarmTile::OnExamine(CVector Pos, CMap* pMap, CEntity* pActor)
{
	PtrList<CEntity*> EntityList = pMap->GetTileEntityList(Pos);
	if(!EntityList.empty()) {
		ExamineEntitieList(EntityList);
		return;
	}

	gMessages.AddMessage("Dies ist ein stueck Farmland");

	FlagSet<Uint8> TileData = pMap->GetTileData(Pos);
	if(TileData.Is_Set(FTD_FULLY_GROWN)) {
		gMessages.AddMessage("Es ist eine Pflanze darauf");
	}
}

bool CFarmTile::IsPassable(CVector Pos, CMap* pMap, CEntity* pTrespasser)
{
	FlagSet<Uint8> TileData = pMap->GetTileData(Pos);
	if(!TileData.Is_Set(FTD_FULLY_GROWN))
		return CMapTile::IsPassable(Pos, pMap, pTrespasser);
	else return false;
}

Tile CFarmTile::GetTile(CVector Pos, CMap* pMap)
{
	FlagSet<Uint8> TileData = pMap->GetTileData(Pos);

	if(TileData.Is_Set(FTD_FULLY_GROWN)) {
		eFarmTileData PlantType = (eFarmTileData)FT_PLANT_TYPE(TileData.raw());
		switch(PlantType) {
		case FTD_PLUMPHELMET:
			return Tile('$', CColor(227,128,182), CColor(0, 0, 0));
		case FTD_BANELING:
			return Tile('B', CColor(0,220,0), CColor(0, 0, 0));
		case FTD_SPINECRAWLER:
			return Tile('S', CColor(40,40,40), CColor(0, 0, 0));
		default:
			return Tile(' ', CColor(0,0,0), CColor(255,0,255));
		}
	}
	return CMapTile::GetTile(Pos, pMap);
}
