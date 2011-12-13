/*
 * CMap.cpp
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#include "Map/CMap.h"

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

/**
 * @function:
 * Zeichnet ein Feld auf den Screenbuffer
 *
 * @origin:
 * Urspr�nglich aus der Funktion DrawMap()
 **/
bool CMap::DrawTile(Screen* s, Uint16 X, Uint16 Y, Uint16 StartX, Uint16 StartY)
{
	if(!(X < MapWidth || Y < MapWidth)) return false;

	if(Tiles[Y][X].Flags.Is_Set(MTF_EXISTANT) && Tiles[Y][X].Flags.Is_Set(MTF_VISIBLE))
		if(!(s->Put(Tiles[Y][X].GetTile(), StartX+X, StartY+Y)))
			return false;
	return true;
}

/**
 * @function:
 * F�llt die gesamte Map mit dem Angegebenen Feld
 *
 * @ClearTile:
 * Das Feld, auf das jedes Feld der Map gesetzt werden soll
 **/
void CMap::ClearMap(CMapTile ClearTile)
{
	for(Uint16 Y=0;Y<MapHeight;Y++)
		for(Uint16 X=0;X<MapWidth;X++)
		{
			Tiles[Y][X].PrepareRemoval();
			Tiles[Y][X] = ClearTile;
		}
}

/**
 * @function:
 * Zeichnet die Karte auf das angegebene Screen Objekt
 *
 * @s:
 * screenbuffer
 *
 * @StartX, StartY:
 * An diesen Koordinaten wird das Linke Obere Feld gezeichnet werden
 * (Alle anderen breiten sich nach Rechtsunten aus)
 * TODO:Implement EndX,EndY for culling
 **/
bool CMap::DrawMap(Screen* s, Uint16 StartX, Uint16 StartY)
{
	if(!s)
		return false;

	bool ret = true;
	for(Uint16 Y=0;Y<MapHeight;Y++)
		for(Uint16 X=0;X<MapWidth;X++)
			if(!DrawTile(s,X,Y,StartX,StartY))
				ret = false;
	return ret;
}

/**
 * @function:
 * Setzt das Feld mit den angegebenen Koordinaten auf T
 *
 * @T:
 * Tile
 *
 * @X,Y:
 * Koordinaten
 **/
void CMap::PutMapTile(CMapTile T, Uint16 X, Uint16 Y)
{
	if(!((X < 0 || X >= MapWidth) || (Y < 0 || Y >= MapHeight)))
	{
		Tiles[Y][X].PrepareRemoval();
		Tiles[Y][X] = T;
	}
}
