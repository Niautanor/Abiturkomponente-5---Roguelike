/*
 * MobEntity.h
 *
 *  Created on: 07.01.2012
 *      Author: Tim
 */

#pragma once  /* MOBENTITY_H_ */

#include "Entities/Entity.h"

#include "Items/Item.h"

#include "HelperAPI/Random.h"

#include "HelperAPI/SmartObject.h"

class CMobEntity : public CEntity
{
protected:
	SmartObject<CItem> WieldedItem;

public:
	CMobEntity(Tile T = Tile('M', CColor(255,0,0), CColor(0,0,0)), CVector Position = CVector(1,1), Uint8 Flags = EF_MOB)
		: CEntity(T, Position, Flags) { }
	virtual ~CMobEntity() {};

	virtual const char* GetName();
	virtual const char* GetDescription();

	virtual Uint8 IsHostile(CEntity* pTarget);

	virtual void PickUp(CMap* pMap, CEntity* pItem);
	virtual void Drop(CMap* pMap);

	virtual void Attack(CMap* pMap, CEntity* pEntity);

	virtual void Tick(CMap* pMap);
};
