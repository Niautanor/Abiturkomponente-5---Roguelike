/*
 * Entity.h
 *
 *  Created on: 18.12.2011
 *      Author: Tim
 */

#pragma once /* ENTITY_H_ */

class CEntity;

enum eEntityFlag
{
	EF_MOB = 0x01,
	//MobFlags
	EF_PLAYER = 0x02
};

enum eHostilityType
{
	HT_NONE,
	HT_ITEM,//An Item doesn't hate anyone and neither anyone hates an item
	HT_HOSTILE,
	HT_FRIENDLY
};

#include "Main/Tile.h"

#include "Map/Map.h"

#include "HelperAPI/FlagSet.h"

#include "HelperAPI/CVector.h"

class CEntity
{
protected:
	Tile default_tile;

public:
	CVector Pos;
	CVector Mov;

public:
	CEntity(Tile T = Tile('E', CColor(255,0,255), CColor(0,0,0)), CVector Position = CVector(1,1), Uint8 Flags = 0);
	virtual ~CEntity();

	virtual const char* GetName();

	virtual bool CanMove(CMap* pMap, CVector Direction);

	//Checks if *this* entity is hostile to the Param-Entity (this should be only relevant in CMobEntity but is included here because of invalid type casts from base to derivate)
	virtual Uint8 IsHostile(CEntity* pEntity);

	virtual void Attack(CMap* pMap, CEntity* pTarget);

	virtual Tile GetTile(CMap* pMap) { return default_tile; }

	virtual void Tick(CMap* pMap);

	FlagSet<Uint8> EntityFlags;
};

#include "Entities/MobEntity.h" //Its a good thing to have them all in one place
