/*
 * Item.h
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#pragma once  /* ITEM_H_ */

#include "HelperAPI/CFactory.h"

/**
 * IMPORTANT: Worked in a little Factory class Hierarchy to enable SmartObjects to create diferent Item classes
 **/

class CItem;

#include "HelperAPI/CNameable.h"
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

class CItem : public CFactory, public CNameable {
public:
	CItem(eItemExtraData ED = IED_NONE, Uint8 Start_Uses = 1);
	virtual ~CItem();

	static CItem* GenerateObject(Uint8 Type);

	virtual eItemType GetType();

	Uint8 /*eItemExtraData*/ ExtraData;
	Uint8 Uses;//Number of remaining uses

	virtual void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};

#include "Items/SeedItem.h"
#include "Items/WeaponItem.h"
