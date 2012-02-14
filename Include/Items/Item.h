/*
 * Item.h
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#pragma once  /* ITEM_H_ */

enum eItemType {
	IT_NO_ITEM = 0,
	IT_WEAPON,
	IT_SEED
};

class CItem {
public:
	CItem();
	virtual ~CItem();

	/*eItemType*/eItemType Type;
};
