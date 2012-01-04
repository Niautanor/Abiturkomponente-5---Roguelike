/*
 * FlagSet.cpp
 *
 *  Created on: 16.10.2011
 *      Author: Tim
 *      
 * NOTE: .inc because it contains only Template definitions which cant be exported to a seperate file
 */

template<class T> FlagSet<T>::FlagSet()
{
	Flags = 0;
}

template<class T> void FlagSet<T>::Clear()
{
	Flags = 0;
}

template<class T> bool FlagSet<T>::Is_Set(T Flag)
{
	return (Flags & Flag);
}

template<class T> void FlagSet<T>::Set(T Flag)
{
	Flags |= Flag;
}

//FIXME: Find The eventual Bug!!!
template<class T> void FlagSet<T>::Unset(T Flag)
{
	Flag = ~Flag;
	Flags &= Flag;
}
