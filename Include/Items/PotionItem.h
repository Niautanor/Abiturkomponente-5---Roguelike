/*
 * Potion.h
 *
 *  Created on: 18.03.2012
 *      Author: Tim
 */

#pragma once  /* POTION_H_ */

#include "Items/UseableItem.h"

class CPotionItem : public CUseableItem {
public:
	CPotionItem(eItemTypeList ItemTypeId) : CUseableItem(ItemTypeId) { }
	~CPotionItem() { }

	eItemType GetType();

	bool RequiresDirection();
	void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};
