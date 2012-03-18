/*
 * Potion.h
 *
 *  Created on: 18.03.2012
 *      Author: Tim
 */

#pragma once  /* POTION_H_ */

#include "Items/Item.h"

class CPotionItem : public CItem {
public:
	CPotionItem() : CItem(IED_NONE, 1) { }
	~CPotionItem() { }

	const char* GetName();
	const char* GetDescription();

	eItemType GetType();

	bool RequiresDirection();
	void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};
