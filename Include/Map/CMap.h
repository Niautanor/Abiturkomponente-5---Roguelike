/*
 * CMap.h
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#pragma once/* CMAP_H_ */

#include "Main/Screen.h"
#include "HelperAPI/CVector.h"
#include "Map/CMapTile.h"

class CMap
{
private:
	Uint16 MapWidth, MapHeight;

	CMapTile** Tiles;

	/*Refractored from DrawMap*/
	bool DrawTile(Screen* s, Uint16 X, Uint16 Y, Uint16 StartX, Uint16 StartY);

public:
	CMap();

	CMapTile* GetTile(Uint16 X, Uint16 Y) {
		if(X < MapWidth && Y < MapHeight)
			return &Tiles[Y][X];
		else return NULL;
	}

	Uint16 GetW() { return MapWidth; }
	Uint16 GetH() { return MapHeight; }

	/*Init und Exit*/
	bool OnInit(Uint16 Width, Uint16 Height);
	void OnExit();

	/*Grundsätzliche Verwaltungsfunktionen*/
	void ClearMap(CMapTile ClearTile);
	bool DrawMap(Screen* s, Uint16 StartX, Uint16 StartY);
	void PutMapTile(CMapTile T, Uint16 X, Uint16 Y);
};
