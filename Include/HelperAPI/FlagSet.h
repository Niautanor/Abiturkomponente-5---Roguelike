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

	void Clear();

	bool Is_Set(T Flag) const;

	void Set(T Flag);
	void Unset(T Flag);

	T raw() const { return Flags; }//returns the Raw Flagset as an integral type
};

#include "HelperAPI/FlagSet.cpp.inc"
