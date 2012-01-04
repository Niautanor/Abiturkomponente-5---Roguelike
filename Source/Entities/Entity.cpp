/*
 * CEntity.cpp
 *
 *  Created on: 19.12.2011
 *      Author: Tim
 */

#include "Entities/Entity.h"

CEntity::CEntity()
{
	default_tile = Tile('@', CColor(255,0,255), CColor(0,0,0));
	Pos = CVector(1,1);
	Mov = CVector(0,0);
}

CEntity::~CEntity()
{
}

bool CEntity::CanMove(CMap* pMap, CVector Dir)
{
	if(pMap->GetTile(Pos+Dir)->IsPassable(Pos+Dir,pMap,this))
		return true;
	return false;
}

void CEntity::Tick(CMap* pMap)
{
	if(CanMove(pMap, Mov))
		Pos += Mov;
	Mov = CVector(0,0);
}
