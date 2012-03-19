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

#include "Items/ItemType.h"

class CItem;

#include "HelperAPI/CNameable.h"
#include "Map/Map.h"

class CItem : public CFactory, public CNameable {
public:
	CItem(eItemTypeList ItemTypeId);
	virtual ~CItem();

	static CItem* GenerateObject(Uint8 Type);

	virtual const char* GetName();
	virtual const char* GetDescription();

	virtual eItemType GetType();
	eItemTypeList GetTypeId();

	eItemTypeList TypeId; //not to be confused with typeid

	bool IsUseable();//A little Helper Function, that tells if an Item Type is useable by Looking at its TypeId

	virtual bool RequiresDirection();
	virtual void OnUse(CVector UsePos, CEntity* pUser, CMap* pMap);
};

#include "Items/UseableItem.h"
#include "Items/WeaponItem.h"
