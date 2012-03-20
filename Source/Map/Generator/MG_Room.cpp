/*
 * MGRoom.cpp
 *
 *  Created on: 05.03.2012
 *      Author: Tim
 */

#include "Map/Generator/MG_Room.h"

MG_Room::MG_Room()
{
	for(unsigned char i = 0; i < 4; i++)
		Doors[i] = false;
	Content = RC_NONE;
	ConnectedToStart = false;
}

MG_Room::~MG_Room()
{
	// TODO Auto-generated destructor stub
}

eDirection MG_Room::GenerateDoors(unsigned char PossibleDoors)
{
	int Direction;
	do {
		Direction = rand() % 4;
	} while(!(IntToeDir(Direction) & PossibleDoors) || Doors[Direction]);

	Doors[Direction] = true;

	return IntToeDir(Direction);
}

bool MG_Room::CanPlaceDoor(unsigned char PossibleDoors)
{
	if ((PossibleDoors & D_LEFT) && !Doors[0])
		return true;
	else if ((PossibleDoors & D_TOP) && !Doors[1])
		return true;
	else if ((PossibleDoors & D_RIGHT) && !Doors[2])
		return true;
	else if ((PossibleDoors & D_BOTTOM) && !Doors[3])
		return true;
	return false;
}

int MG_Room::NumDoors()
{
	int Ret = 0;
	for (unsigned char i = 0; i < 4; i++)
		if (Doors[i])
			++Ret;
	return Ret;
}
