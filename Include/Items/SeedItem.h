/*
 * CSeedItem.h
 *
 *  Created on: 11.03.2012
 *      Author: Tim
 */

#pragma once  /* CSEEDITEM_H_ */

#include "Items/Item.h"

class CSeedItem : public CItem {
public:
	CSeedItem(eItemExtraData ExtraData) : CItem(ExtraData, 1) { }
	~CSeedItem() { }

	const char* GetName();
	const char* GetDescription();

	eItemType GetType();

	void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};
