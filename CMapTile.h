/*
 * CMapTile.h
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#pragma once/* CMAPTILE_H_ */

#include "Unicode.h"

#include "Tile.h"

class CMapTile : public Tile
{
public:
	CMapTile();
	CMapTile(Tile t);
};
