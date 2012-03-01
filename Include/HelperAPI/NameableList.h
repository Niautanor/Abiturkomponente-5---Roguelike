/*
 * NameableList.h
 *
 *  Created on: 29.02.2012
 *      Author: Tim
 */

#pragma once  /* NAMEABLELIST_H_ */

#include "HelperAPI/CNameable.h"

#include "HelperAPI/PtrList.h"

class CNameableList_Entry : public CNameable {
private:
	const char* Name;
	const char* Description;

public:
	CNameableList_Entry(const char* N = "", const char* D = "") : Name(N), Description(D) { }
	~CNameableList_Entry() { }

	const char* GetName() { return Name; }
	const char* GetDescription() { return Description; }
};

PtrList<CNameableList_Entry*> CreateNameList(int ammount, const char* Names[]);
