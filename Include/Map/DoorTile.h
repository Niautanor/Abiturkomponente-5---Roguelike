/*
 * DoorTile.h
 *
 *  Created on: 03.01.2012
 *      Author: Tim
 */

#pragma once  /* DOORTILE_H_ */

#include "Map/MapTile.h"

class CDoorTile : public CMapTile
{
private:
	bool Open;

public:
	CDoorTile(Tile t, MapTileFlag Flagset) : CMapTile(t, Flagset) { Open = false; }

	void OnInteract(CVector Pos, CMap* pMap, CEntity* pActor);
	void OnExamine(CVector Pos, CMap* pMap, CEntity* pActor);

	Tile GetTile(CVector Pos, CMap* pMap);
};
