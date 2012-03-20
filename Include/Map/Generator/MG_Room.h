/*
 * MGRoom.h
 *
 *  Created on: 05.03.2012
 *      Author: Tim
 */

//MapGenerator_Room

#pragma once /* MGROOM_H_ */

#include <stdlib.h>

enum eDirection {
	D_NONE = 0x00,
	D_LEFT = 0x01,
	D_TOP = 0x02,
	D_RIGHT = 0x04,
	D_BOTTOM = 0x08,
	D_ALL = 0x0F
};

enum eRoomContent {
	RC_NONE = 0x00,
	RC_MONSTER,
	RC_LOOT,
	RC_FARMLAND,
	RC_EXIT
};

inline int eDirToInt(eDirection D) {
	int Ret = 0;
	int RawDir = D;
	while(!(D & D_LEFT)) {
		++Ret;
		RawDir >>= 1;
	}
	return Ret;
}

inline eDirection IntToeDir(int D) {
	switch(D) {
	case 0: return D_LEFT;
	case 1: return D_TOP;
	case 2: return D_RIGHT;
	case 3: return D_BOTTOM;
	default: return D_NONE;
	}
}

class MG_Room {
public:
	bool Doors[4];
	eRoomContent Content;
	bool ConnectedToStart;

	//Returns the Direction in which the door is placed
	eDirection GenerateDoors(unsigned char PossibleDoors);

	int NumDoors();

	bool CanPlaceDoor(unsigned char PossibleDoors);

	MG_Room();
	~MG_Room();
};

