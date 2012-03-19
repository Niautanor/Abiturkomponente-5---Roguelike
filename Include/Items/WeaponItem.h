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
	CWeaponItem(eItemTypeList ItemTypeId) : CItem(ItemTypeId) { }
	~CWeaponItem() { }

	eItemType GetType();

	void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};
