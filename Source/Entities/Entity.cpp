/*
 * CEntity.cpp
 *
 *  Created on: 19.12.2011
 *      Author: Tim
 */

#include "Entities/Entity.h"

CEntity::CEntity(Tile T, CVector Position, Uint8 Flags)
{
	default_tile = T;

	Pos = Position;
	Mov = CVector(0,0);

	EntityFlags.Clear();
	EntityFlags.Set(Flags);
}

CEntity::~CEntity()
{
}

//This should NEVER ever Hapen
const SmartObjectList<CItem>& CEntity::GetInventory()
{
	throw "Ich bin kein Mob du Idiot";
}

const char* CEntity::GetName() const
{
	return "Entity-Objekt";
}


const char *CEntity::GetDescription() const
{
	return "Entity-Beschreibung";
}

bool CEntity::CanMove(CMap* pMap, CVector Dir)
{
	if(pMap->GetTile(Pos+Dir)->IsPassable(Pos+Dir,pMap,this))
		return true;
	return false;
}

Uint8 CEntity::IsHostile(CEntity *pEntity)
{
	return HT_ITEM;
}

bool CEntity::IsPlayer()
{
	return false;
}

void CEntity::Attack(CMap *pMap, CEntity *pTarget)
{//Purely virtual(Items don't attack
}

void CEntity::GetHurt(Uint8 Damage, CMap* pMap, CEntity* pAttacker)
{//same counts for getting hurt
}

bool CEntity::IsAlive(CMap* pMap)
{
	return true;//Items aren't really alive but they can not be removed when they die... -.-
}

void CEntity::PickUp(CMap* pMap, CEntity* pItem)
{
}

void CEntity::Drop(CMap* pMap, Uint8 InventoryId)
{
}

void CEntity::WieldItem(CMap* pMap, Uint8 InventoryId)
{
}

void CEntity::UnwieldItem(CMap* pMap)
{
}

eItemType CEntity::GetItemType() const
{
	return IT_NO_ITEM;
}

void CEntity::SetItemType(eItemType Type)
{
}

Uint8 CEntity::GetExtraData(CMap *pMap)
{
	return 0;
}

void CEntity::SetExtraData(Uint8 ExtraData)
{
}

bool CEntity::WieldsItem()
{
	return false;
}

void CEntity::UseItem(CVector Direction, CMap* pMap)
{
}

void CEntity::Tick(CMap* pMap)
{
	if(Mov != CVector(0,0) && CanMove(pMap, Mov))
		Pos += Mov;
	Mov = CVector(0,0);
}
