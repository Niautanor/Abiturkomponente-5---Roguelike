/*
 * CSeedItem.h
 *
 *  Created on: 11.03.2012
 *      Author: Tim
 */

#pragma once  /* CSEEDITEM_H_ */

#include "Items/UseableItem.h"

class CSeedItem : public CUseableItem {
public:
	CSeedItem(eItemTypeList ItemTypeId) : CUseableItem(ItemTypeId) { }
	~CSeedItem() { }

	eItemType GetType();

	bool RequiresDirection();
	void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};
