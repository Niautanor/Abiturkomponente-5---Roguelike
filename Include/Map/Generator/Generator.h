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
	char* Tiles;
	MG_Room* Rooms;

	Uint16 NumRoomsX, NumRoomsY;
	Uint16 MapW, MapH; //MapW and H are for the Tile version of the map(not for the symbol like rooms)

public:
	MapGenerator();
	~MapGenerator();

	bool Init(Uint16 MinW, Uint16 MaxW, Uint16 MinH, Uint16 MaxH);
	void Exit();

	Uint16 XRooms() { return NumRoomsX; }
	Uint16 YRooms() { return NumRoomsY; }

	Uint16 W() { return MapW; }
	Uint16 H() { return MapH; }

	char& GetTile(Uint16 X, Uint16 Y) { return Tiles[Y * MapW + X]; }
	MG_Room* GetRoom(Uint16 X, Uint16 Y) { return &(Rooms[Y * NumRoomsX + X]); }
};

