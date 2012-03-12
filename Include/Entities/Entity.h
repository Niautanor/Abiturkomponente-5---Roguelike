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
	EF_PLAYER = 0x02,
	//ItemFlags(0x01 is reserved for the MOB-Flag
	EF_IT_WEAPON = 0x02,
	EF_IT_SEED = 0x04
};

enum eItemType {
	IT_NO_ITEM = 0,
	IT_WEAPON,
	IT_SEED
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

#include "Items/Item.h"

#include "HelperAPI/FlagSet.h"

#include "HelperAPI/CVector.h"

#include "HelperAPI/CNameable.h"

class CEntity : public CNameable
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
	virtual const char* GetDescription();

	virtual bool CanMove(CMap* pMap, CVector Direction);

	//Checks if *this* entity is hostile to the Param-Entity (this should be only relevant in CMobEntity but is included here because of invalid type casts from base to derivate)
	virtual Uint8 IsHostile(CEntity* pEntity);

	//Mobs Pick stuff up and stuff
	virtual void PickUp(CMap* pMap, CEntity* pItem);
	virtual void Drop(CMap* pMap);

	//Used for picking up ItemEntities purely virtual in all other cases
	virtual eItemType GetItemType();
	virtual void SetItemType(eItemType Type);

	//Currently only used for Items to store Seed-/Weapon type and so on
	virtual Uint8 GetExtraData(CMap* pMap);
	virtual void SetExtraData(Uint8 ExtraData);

	//Entity is Player
	virtual bool IsPlayer();

	virtual void Attack(CMap* pMap, CEntity* pTarget);
	virtual void GetHurt(Uint8 Damage, CMap* pMap, CEntity* pAttacker);
	virtual bool IsAlive(CMap* pMap);

	//Purely Virtual in non Mob-Classes
	virtual bool WieldsItem();
	virtual void UseItem(CVector Direction, CMap* pMap);

	virtual Tile GetTile(CMap* pMap) { return default_tile; }

	virtual void Tick(CMap* pMap);

	FlagSet<Uint8> EntityFlags;
	//Uint8 ExtraData;//Mainly used for ItemEntities(Maybe i can squeeze Health information in it)
};

//Forward Declarations
class CMobEntity;
class CItemEntity;
//Forward End

#include "Entities/MobEntity.h" //Its a good thing to have them all in one place
#include "Entities/ItemEntity.h"
