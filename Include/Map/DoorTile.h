/*
 * DoorTile.h
 *
 *  Created on: 03.01.2012
 *      Author: Tim
 */

#pragma once  /* DOORTILE_H_ */

#include "Map/MapTile.h"

enum eDoorTileData
{
	DTD_NONE = 0,
	DTD_OPEN = 0x01
};

class CDoorTile : public CMapTile
{
public:
	CDoorTile(Tile t, MapTileFlag Flagset) : CMapTile(t, Flagset) { }

	void OnInteract(CVector Pos, CMap* pMap, CEntity* pActor);
	void OnExamine(CVector Pos, CMap* pMap, CEntity* pActor);

	bool IsPassable(CVector Pos, CMap* pMap, CEntity* pTrespasser);
	Tile GetTile(CVector Pos, CMap* pMap);
};
