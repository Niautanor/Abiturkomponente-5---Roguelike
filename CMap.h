/*
 * CMap.h
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#pragma once/* CMAP_H_ */

#include "Unicode.h"
#include "Screen.h"
#include "CMapTile.h"

class CMap
{
private:
	Uint16 MapWidth, MapHeight;

	CMapTile** Tiles;

	/*Refractored from DrawMap*/
	bool DrawTile(Screen* s, Uint16 X, Uint16 Y, Uint16 StartX, Uint16 StartY);

public:
	CMap();

	/*Init und Exit*/
	bool OnInit(Uint16 Width, Uint16 Height);
	void OnExit();

	/*Grundsätzliche Verwaltungsfunktionen*/
	void ClearMap(CMapTile ClearTile);
	bool DrawMap(Screen* s, Uint16 StartX, Uint16 StartY);
	void PutMapTile(CMapTile T, Uint16 X, Uint16 Y);

	/*TileFlags abrufen und setzen*/
	bool GetTileFlag(Uint16 X, Uint16 Y, MapTileFlag Flag);
	void SetTileFlag(Uint16 X, Uint16 Y, MapTileFlag Flag);
	void UnsetTileFlag(Uint16 X, Uint16 Y, MapTileFlag Flag);
};
