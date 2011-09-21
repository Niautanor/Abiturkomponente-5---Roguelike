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

public:
	CMap();

	bool OnInit(Uint16 Width, Uint16 Height);
	void OnExit();

	void ClearMap(CMapTile ClearTile);

	void PutMapTile(CMapTile T, Uint16 X, Uint16 Y);

	bool DrawMap(Screen* s, Uint16 StartX, Uint16 StartY);
};
