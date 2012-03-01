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
	SIED_SPINECRAWLER = 0x30,
	SIED_BANELING = 0x40,
	SIED_MOBSTERPLANT = 0x50,
	SIED_CANCER_CURE = 0x60
};

class CItem {
public:
	CItem(eItemType T = IT_NO_ITEM, eItemExtraData ED = IED_NONE, Uint8 Start_Uses = 1);
	virtual ~CItem();

	eItemType Type;
	Uint8 /*eItemExtraData*/ ExtraData;
	Uint8 Uses;//Number of remaining uses

	virtual void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};
