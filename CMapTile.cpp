/*
 * CMapTile.cpp
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#include "CMapTile.h"

CMapTile::CMapTile() : Tile('\0', CColor(255,255,255), CColor(0,0,0))
{
}

CMapTile::CMapTile(Tile t)
{
	this->C = t.C;
	this->fg = t.fg;
	this->bg = t.bg;
}
