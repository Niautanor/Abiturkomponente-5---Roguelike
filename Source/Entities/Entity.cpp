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

const char* CEntity::GetName()
{
	return "Entity-Objekt";
}


const char *CEntity::GetDescription()
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

void CEntity::Attack(CMap *pMap, CEntity *pTarget)
{//Purely virtual(Items dont attack
}

void CEntity::PickUp(CMap* pMap, CEntity* pItem)
{
}

void CEntity::Drop(CMap* pMap)
{
}

eItemType CEntity::GetItemType(CMap* pMap)
{
	return IT_NO_ITEM;
}

void CEntity::SetItemType(eItemType Type)
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
	if(CanMove(pMap, Mov))
		Pos += Mov;
	Mov = CVector(0,0);
}
