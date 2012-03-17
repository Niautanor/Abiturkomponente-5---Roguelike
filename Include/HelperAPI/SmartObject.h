/*
 * SmartObject.h
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#pragma once  /* SMARTOBJECT_H_ */

#include "HelperAPI/CFactory.h"
#include <stdlib.h>

template<class C> class SmartObject { //IMPORTANT: C should be a Derived class of CFactory
private:
	C* pC;
public:
	SmartObject() { pC = NULL; }
	SmartObject(const SmartObject& O) { pC = NULL; }
	SmartObject(Uint8 Type) { pC = NULL; New(Type); }
	~SmartObject() { Delete(); }

	inline operator C* () const {
		return pC;
	}

	inline void New(Uint8 Type) {
		Delete();
		pC = C::GenerateObject(Type);
		if(!pC) throw "GenerateExeption of CFactory";
	}
	inline void Delete() {
		if(pC)
		{
			delete pC;
			pC = NULL;
		}
	}

	inline C* operator -> () const {
		return pC;
	}

	inline operator bool () const {
		if(pC) return true;
		else return false;
	}
};
