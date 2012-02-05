/*
 * CNameable.h
 *
 *  Created on: 05.02.2012
 *      Author: Tim
 *
 *  @purpose: Eine Basisklasse für alle sachen die einen Namen oder eine Beschreibung haben
 */

#pragma once  /* CNAMEABLE_H_ */

class CNameable {
public:
	CNameable();
	virtual ~CNameable();

	virtual const char* GetName();
	virtual const char* GetDescription();
};
