/*
 * Player.cpp
 *
 *  Created on: 12.03.2012
 *      Author: Tim
 */

#include "Entities/Player.h"

const char* CPlayer::GetName()
{
	return "Du selbst";
}

const char* CPlayer::GetDescription()
{
	return "Du bist ein Geiler Abenteurer";
}

bool CPlayer::IsPlayer()
{
	return true;
}

void CPlayer::Attack(CMap* pMap, CEntity* pTarget)
{
	CWeaponType* pWeaponType;
	if(WieldedItem && WieldedItem->GetType() == IT_WEAPON) {
		pWeaponType = (CWeaponType*) CItemTypeList::GetType(WieldedItem->TypeId);
	} else {
		pWeaponType = (CWeaponType*)CItemTypeList::GetType(ITL_FIST_WEAPON);
	}

	if(Chance(pWeaponType->HitPercentage)) {
		pTarget->GetHurt(pWeaponType->Damage, pMap, this);
	} else gMessages.AddFMessage("Du verfehlst den %s", pTarget->GetName());

	CMobEntity::Attack(pMap, pTarget);
}

