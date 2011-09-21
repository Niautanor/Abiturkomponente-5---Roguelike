/*
 * CMapTile.cpp
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#include "CMapTile.h"

CMapTile::CMapTile()
{
	T = Tile('\0', CColor(255,255,255), CColor(0,0,0));
}

CMapTile::CMapTile(Tile t)
{
	T = t;
}

bool CMapTile::PutToScreen(Screen* s, Uint16 X, Uint16 Y)
{
	if(!s)return NULL;
	return s->Put(T, X, Y);
}
