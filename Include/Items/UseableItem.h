/*
 * UseableItem.h
 *
 *  Created on: 19.03.2012
 *      Author: Tim
 */

#pragma once  /* USEABLEITEM_H_ */

//class CUseableItem;

#include "Items/Item.h"

class CUseableItem : public CItem {
public:
	CUseableItem(eItemTypeList ItemTypeId);

	Uint8 Uses;

	virtual void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};

#include "Items/SeedItem.h"
#include "Items/PotionItem.h"
