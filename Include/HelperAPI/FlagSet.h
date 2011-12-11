/*
 * FlagSet.h
 *
 *  Created on: 16.10.2011
 *      Author: Tim
 */

#pragma once/* FLAGSET_H_ */

template<class T> class FlagSet
{
private:
	T Flags;

public:
	FlagSet();

	bool Is_Set(T Flag);

	void Set(T Flag);
	void Unset(T Flag);
};

#include "HelperAPI/FlagSet.cpp.inc"
