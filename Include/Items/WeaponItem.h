/*
 * WeaponItem.h
 *
 *  Created on: 11.03.2012
 *      Author: Tim
 */

#pragma once  /* WEAPONITEM_H_ */

#include "Items/Item.h"

class CWeaponItem : public CItem {
public:
	CWeaponItem(eItemExtraData ExtraData = IED_NONE, Uint8 RemainingUses = 5) : CItem(ExtraData, RemainingUses) { }
	~CWeaponItem() { }

	const char* GetName();
	const char* GetDescription();

	eItemType GetType();

	void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};
