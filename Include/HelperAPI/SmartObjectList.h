/*
 * SmartObjectList.h
 *
 *  Created on: 16.03.2012
 *      Author: Tim
 */

#pragma once  /* SMARTOBJECTLIST_H_ */

#include <vector>
#include "HelperAPI/SmartObject.h"

template<class C> class SmartObjectList {
private:
	std::vector<SmartObject<C> > List;

public:
	void clear() { List.clear(); }
	size_t size() const { return List.size(); }
	bool empty() const;//isn't a regular List.empty because i wanted to know if there are actual Items in the List

	C* operator [] (Uint32 i) { return List[i]; }
	const C* operator [] (Uint32 i) const { return List[i]; }

	int Push(Uint8 Type);
	void Delete(Uint32 Id);
};

template<class C> bool SmartObjectList<C>::empty() const
{
	for(Uint32 i=0;i<List.size();i++)
		if(List[i])
			return false;
	return true;
}

template<class C> int SmartObjectList<C>::Push(Uint8 Type)
{
	for(Uint32 i=0;i<size();i++) {
		if(!List[i]) {
			List[i].New(Type);
			return i;
		}
	}
	List.push_back(SmartObject<C>());//Has to be that complicated because copying Pointers of Smart Objects causes Memory Corruption
	Uint32 Id = (List.size() - 1);
	List[Id].New(Type);
	return Id;
}

template<class C> void SmartObjectList<C>::Delete(Uint32 Id)
{
	if(Id >= size()) return;

	List[Id].Delete();
}
