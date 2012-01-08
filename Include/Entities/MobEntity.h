/*
 * MobEntity.h
 *
 *  Created on: 07.01.2012
 *      Author: Tim
 */

#pragma once  /* MOBENTITY_H_ */

#include "Entities/Entity.h"

#include "HelperAPI/Random.h"

class CMobEntity : public CEntity
{
public:
	CMobEntity(Tile T = Tile('M', CColor(255,0,0), CColor(0,0,0)), CVector Position = CVector(1,1), Uint8 Flags = EF_MOB)
		: CEntity(T, Position, Flags) { }
	virtual ~CMobEntity() {};

	virtual void Tick(CMap* pMap);
};
