/*
 * CMapTile.h
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#pragma once/* CMAPTILE_H_ */

class CMapTile;

#include "HelperAPI/FlagSet.h"

#include "Main/Tile.h"

#include "Map/Map.h"

#include "HelperAPI/PtrList.h"
#include "Entities/Entity.h"

typedef Uint16 MapTileFlag;

enum eMapTileFlags
{
	MTF_EXISTANT = 0x0001,
	MTF_VISIBLE = 0x0002,
	MTF_PASSABLE = 0x0004
};

class CMapTile
{
private:
	Tile FloorTile;

public:
	CMapTile() : FloorTile(Tile(' ',CColor(0,0,0),CColor(255,255,255))) { Flags.Clear(); }
	CMapTile(Tile t, MapTileFlag Flagset);

	static CMapTile* EmptyTile;
	static CMapTile* WallTile;
	static CMapTile* GroundTile;

	FlagSet<Uint16> Flags;

	virtual void Tick(CVector Pos, CMap* pMap);

	/**
	 * @function: Returns the drawable colored Character of the mapTile
	 * by default the FloorTile
	 * which can be replaced by Entitys on the Tile
	 **/
	Tile GetTile(CVector Pos, CMap* pMap);
};
