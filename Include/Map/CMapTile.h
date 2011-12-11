/*
 * CMapTile.h
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#pragma once/* CMAPTILE_H_ */

#include "HelperAPI/Unicode.h"

#include "HelperAPI/FlagSet.h"

#include "Main/Tile.h"

typedef Uint16 MapTileFlag;

enum eMapTileFlags
{
	MTF_EXISTANT = 0x0001,
	MTF_VISIBLE = 0x0002,
	MTF_SOLIT = 0x0003
};

class CMapTile
{
private:
	Tile FloorTile;

public:
	CMapTile();
	CMapTile(Tile t, MapTileFlag Flagset);

	FlagSet<Uint16> Flags;

	void PrepareRemoval();

	Tile GetTile();
};
