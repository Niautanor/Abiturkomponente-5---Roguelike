/*
 * ItemEntity.h
 *
 *  Created on: 05.02.2012
 *      Author: Tim
 */

#pragma once  /* ITEMENTITY_H_ */

#include "Entities/Entity.h"

class CItemEntity : public CEntity {
public:
	CItemEntity(Tile T = Tile('E', CColor(255,0,255), CColor(0,0,0)), CVector Position = CVector(1,1), Uint8 Flags = 0) : CEntity(T, Position, Flags) { }
	virtual ~CItemEntity() { }

	virtual const char* GetName();
	virtual const char* GetDescription();

	Uint8 IsHostile(CEntity* pEntity) { return HT_ITEM; };

	eItemType GetItemType(CMap* pMap);
	void SetItemType(eItemType Type);
};
