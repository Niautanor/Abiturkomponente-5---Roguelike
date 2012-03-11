/*
 * WeaponItem.cpp
 *
 *  Created on: 11.03.2012
 *      Author: Tim
 */

#include "Items/WeaponItem.h"

const char* CWeaponItem::GetName()
{
	return "Waffe";
}

const char* CWeaponItem::GetDescription()
{
	return "Es ist scharf spitz und spritzig";
}

eItemType CWeaponItem::GetType()
{
	return IT_WEAPON;
}

void CWeaponItem::OnUse(CVector UsePos, CEntity* pUser, CMap* pMap)
{
}

