/*
 * SmartObject.h
 *
 *  Created on: 14.02.2012
 *      Author: Tim
 */

#pragma once  /* SMARTOBJECT_H_ */

template<class C> class SmartObject {
private:
	C* pC;
public:
	SmartObject() { pC = 0x00; }
	~SmartObject() { Delete(); }

	inline operator C* () {
		return pC;
	}

	inline void New() {
		Delete();
		pC = new C();
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
