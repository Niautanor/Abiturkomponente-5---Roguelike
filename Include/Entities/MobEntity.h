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
	Sint16 Health;
	Sint16 MaxHealth;

public:
	CMobEntity(Tile T = Tile('M', CColor(255,0,0), CColor(0,0,0)), CVector Position = CVector(1,1), Uint8 Flags = EF_MOB, Sint16 Initial_Health = 20, Sint16 Maximal_Health = 20)
		: CEntity(T, Position, Flags), Health(Initial_Health), MaxHealth(Maximal_Health) { }
	virtual ~CMobEntity() { }

	SmartObject<CItem> WieldedItem;

	virtual const char* GetName();
	virtual const char* GetDescription();

	virtual Uint8 IsHostile(CEntity* pTarget);

	virtual void PickUp(CMap* pMap, CEntity* pItem);
	virtual void Drop(CMap* pMap);

	virtual void Attack(CMap* pMap, CEntity* pTarget);
	virtual void GetHurt(Uint8 Damage, CMap* pMap, CEntity* pAttacker);
	virtual void GetHealed(Uint8 Heal);
	virtual Sint16 GetHealth();
	virtual Sint16 GetMaxHealth();
	virtual bool IsAlive(CMap* pMap);

	virtual bool WieldsItem();
	virtual void UseItem(CVector Dir, CMap* pMap);

	virtual void Tick(CMap* pMap);
};

//Derived Classes
#include "Entities/Player.h"
