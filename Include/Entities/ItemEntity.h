/*
 * ItemEntity.h
 *
 *  Created on: 05.02.2012
 *      Author: Tim
 */

#pragma once  /* ITEMENTITY_H_ */

#include "Entities/Entity.h"

class CItemEntity : public CEntity {
private:
	void InitFromItemData(eItemType Type, eItemTypeList ItemTypeId, CVector Position);

public:
	CItemEntity(Tile T = Tile('E', CColor(255,0,255), CColor(0,0,0)), CVector Position = CVector(1,1), Uint8 Flags = 0) : CEntity(T, Position, Flags) { TypeId = ITL_NONE; }
	CItemEntity(CItem* pItem, CVector Position = CVector());
	CItemEntity(eItemType Type, eItemTypeList ItemTypeId, CVector Position = CVector());

	virtual ~CItemEntity() { }

	eItemTypeList TypeId;

	virtual const char* GetName();
	virtual const char* GetDescription();

	Uint8 IsHostile(CEntity* pEntity) { return HT_ITEM; };

	eItemType GetItemType();
	void SetItemType(eItemType Type);

	eItemTypeList GetItemTypeId(CMap* pMap);
	void SetItemTypeId(eItemTypeList ItemTypeId);
};
