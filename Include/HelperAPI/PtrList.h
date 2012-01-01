/*
 * PtrList.h
 *
 *  Created on: 18.12.2011
 *      Author: Tim
 */

#pragma once  /* PTRLIST_H_ */

#include <vector>

template<class P> class PtrList
{
private:
	std::vector<P> List;

public:
	size_t size() { return List.size();	}
	bool empty() { return List.empty(); }
	void clear() { List.clear(); }

	P& operator [](Uint32 i) { return List[i]; }

	void Push(P Entry);
	int GetId(P Entry);
	void Remove(int Id);
	void Remove(P Entry);
};

template<class P> void PtrList<P>::Push(P Entry)
{
	for (Uint32 i = 0; i < List.size(); i++) {
		if (List[i] == NULL) {
			List[i] = Entry;
			return;
		}
	}
	List.push_back(Entry);
}

template<class P> int PtrList<P>::GetId(P Entry)
{
	for (Uint32 i = 0; i < List.size(); i++)
		if (List[i] == Entry)
			return i;
	return -1;
}

template<class P> void PtrList<P>::Remove(int Id)
{
	if (List[Id] != NULL)
	{
		delete List[Id];
		List[Id] = NULL;
	}
}

template<class P> void PtrList<P>::Remove(P Entry)
{
	int Id = GetId(Entry);
	if(Id >= 0) Remove(Id);
}
