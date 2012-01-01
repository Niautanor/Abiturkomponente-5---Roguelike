/*
 * Entity.h
 *
 *  Created on: 18.12.2011
 *      Author: Tim
 */

#pragma once /* ENTITY_H_ */

class CEntity;

#include "Main/Tile.h"

#include "Map/Map.h"

#include "HelperAPI/CVector.h"

class CEntity
{
protected:
	Tile default_tile;

public:
	CVector Pos;
	CVector Mov;

public:
	CEntity();
	virtual ~CEntity();

	virtual bool CanMove(CMap* pMap, CVector Direction);

	virtual Tile GetTile(CMap* pMap) { return default_tile; }

	virtual void Tick(CMap* pMap);
};
