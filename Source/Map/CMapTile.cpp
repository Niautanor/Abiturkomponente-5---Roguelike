/*
 * CMapTile.cpp
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#include "Map/CMapTile.h"

CMapTile::CMapTile()
{
	FloorTile = Tile('\0', CColor(255,255,255), CColor(0,0,0));
	this->Flags.Clear();
	this->Flags.Set(MTF_EXISTANT);
}

CMapTile::CMapTile(Tile t, MapTileFlag Flagset)
{
	FloorTile = t;

	this->Flags.Clear();
	this->Flags.Set(Flagset);
}

/**
 * @function: Prepares the Tile for Removal(resets all settings and clears all pointing Entitys)
 **/
void CMapTile::PrepareRemoval()
{

}

/**
 * @function: Returns the drawable colored Character of the mapTile
 * by default the FloorTile
 * which can be replaced by Entitys on the Tile
 **/
Tile CMapTile::GetTile()
{
	return FloorTile;
}
