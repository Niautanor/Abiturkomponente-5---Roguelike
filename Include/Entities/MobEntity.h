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

	Sint16 Health;

public:
	CMobEntity(Tile T = Tile('M', CColor(255,0,0), CColor(0,0,0)), CVector Position = CVector(1,1), Uint8 Flags = EF_MOB, Uint8 Initial_Health = 5)
		: CEntity(T, Position, Flags), Health(Initial_Health) { }
	virtual ~CMobEntity() {};

	virtual const char* GetName();
	virtual const char* GetDescription();

	virtual Uint8 IsHostile(CEntity* pTarget);

	virtual void PickUp(CMap* pMap, CEntity* pItem);
	virtual void Drop(CMap* pMap);

	virtual void Attack(CMap* pMap, CEntity* pEntity);
	virtual void GetHurt(Uint8 Damage, CMap* pMap, CEntity* pAttacker);
	virtual bool IsAlive(CMap* pMap);

	virtual bool WieldsItem();
	virtual void UseItem(CVector Dir, CMap* pMap);

	virtual void Tick(CMap* pMap);
};
