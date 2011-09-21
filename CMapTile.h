/*
 * CMapTile.h
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#pragma once/* CMAPTILE_H_ */

#include "Unicode.h"

#include "Screen.h"

class CMapTile
{
public:
	CMapTile();
	CMapTile(Tile t);

	Tile T;

	bool PutToScreen(Screen* s, Uint16 X, Uint16 Y);
};
