/*
 * CFactory.h
 *
 *  Created on: 10.03.2012
 *      Author: Tim
 */

#pragma once  /* CFACTORY_H_ */

#include <SDL/SDL_types.h>

class CFactory {
public:
	CFactory() { };
	virtual ~CFactory() { };

	static CFactory* GenerateObject(Uint8 Type) { return NULL; }
};
