/*
 * Player.cpp
 *
 *  Created on: 12.03.2012
 *      Author: Tim
 */

#include "Entities/Player.h"

const char* CPlayer::GetName() const
{
	return "Du selbst";
}

const char* CPlayer::GetDescription() const
{
	return "Du bist ein Geiler Abenteurer";
}

bool CPlayer::IsPlayer()
{
	return true;
}

void CPlayer::Attack(CMap* pMap, CEntity* pTarget)
{
	if(WieldsItem() && Inventory[0]->GetType() == IT_WEAPON)
		pTarget->GetHurt(3, pMap, this);
	else pTarget->GetHurt(1, pMap, this);

	CMobEntity::Attack(pMap, pTarget);
}

