/*
 * MapGenerator.h
 *
 *  Created on: 05.03.2012
 *      Author: Tim
 */

#pragma once /* MAPGENERATOR_H_ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <SDL/SDL_types.h>

#include "Map/Generator/MG_Room.h"

class MapGenerator {
public:
	Uint16 MapW, MapH;
	MG_Room* Rooms;

	MapGenerator();
	~MapGenerator();

	bool Init(Uint16 MinW, Uint16 MaxW, Uint16 MinH, Uint16 MaxH);
	void Exit();

	MG_Room* GetRoom(Uint16 X, Uint16 Y) { return &(Rooms[Y * MapW + X]); }
};

