/*
 * Item.h
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#pragma once  /* ITEM_H_ */

class CItem;

#include "Map/Map.h"

enum eItemExtraData {
	IED_NONE = 0,
	//if(Type == IT_SEED)
	SIED_PLUMPHELMET = 0x20,//Seed Item Extra Data
	SIED_SPINECRAWLER = 0x40,
	SIED_BANELING = 0x60,
	SIED_MOBSTERPLANT = 0x80,
	SIED_CANCER_CURE = 0xA0
};

class CItem {
public:
	CItem();
	virtual ~CItem();

	eItemType Type;
	Uint8 /*eItemExtraData*/ ExtraData;

	virtual void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};
