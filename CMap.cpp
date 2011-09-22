/*
 * CMap.cpp
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#include "CMap.h"

CMap::CMap()
{
	MapWidth = MapHeight = 0;
	Tiles = NULL;
}

bool CMap::OnInit(Uint16 Width, Uint16 Height)
{
	if(!Width || !Height)
		return false;
	MapWidth = Width;
	MapHeight = Height;

	Tiles = new CMapTile*[MapHeight];
	for(Uint16 i=0;i<MapHeight;i++)
		Tiles[i] = new CMapTile[MapWidth];

	return true;
}

void CMap::OnExit()
{
	for(Uint16 i=0;i<MapHeight;i++)
		delete[] Tiles[i];
	delete[] Tiles;
	Tiles = NULL;
}

void CMap::ClearMap(CMapTile ClearTile)
{
	for(Uint16 Y=0;Y<MapHeight;Y++)
		for(Uint16 X=0;X<MapWidth;X++)
			Tiles[Y][X] = ClearTile;
}

void CMap::PutMapTile(CMapTile T, Uint16 X, Uint16 Y)
{
	Tiles[Y][X] = T;
}

bool CMap::DrawMap(Screen* s, Uint16 StartX, Uint16 StartY)
{
	if(!s)
		return false;

	bool ret = true;
	for(Uint16 Y=0;Y<MapHeight;Y++)
		for(Uint16 X=0;X<MapWidth;X++)
			if(!(s->Put(Tiles[Y][X], StartX+X, StartY+Y)))
				ret = false;
	return ret;
}
