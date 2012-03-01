/*
 * NameableList.cpp
 *
 *  Created on: 29.02.2012
 *      Author: Tim
 */

#include "../../Include/HelperAPI/NameableList.h"

PtrList<CNameableList_Entry*> CreateNameList(int ammount, const char* Names[])
{
	PtrList<CNameableList_Entry*> RetList(true);

	for(Uint16 i=0;i<ammount;i++) {
		RetList.Push(new CNameableList_Entry(Names[i], ""));
	}

	return RetList;
}
