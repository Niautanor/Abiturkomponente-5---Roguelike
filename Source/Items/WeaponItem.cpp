/*
 * WeaponItem.cpp
 *
 *  Created on: 11.03.2012
 *      Author: Tim
 */

#include "Items/WeaponItem.h"

eItemType CWeaponItem::GetType()
{
	return IT_WEAPON;
}

void CWeaponItem::OnUse(CVector UsePos, CEntity* pUser, CMap* pMap)
{
}

