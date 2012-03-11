/*
 * SmartObject.h
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#pragma once  /* SMARTOBJECT_H_ */

#include "HelperAPI/CFactory.h"

template<class C> class SmartObject { //IMPORTANT: C should be a Derived class of CFactory
private:
	C* pC;
public:
	SmartObject() { pC = 0x00; }
	~SmartObject() { Delete(); }

	inline operator C* () {
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
			pC = 0x00;
		}
	}

	inline C* operator -> () {
		return pC;
	}

	inline operator bool () {
		if(pC) return true;
		else return false;
	}
};
