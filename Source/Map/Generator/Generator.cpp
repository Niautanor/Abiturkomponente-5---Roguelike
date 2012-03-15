/*
 * MapGenerator.cpp
 *
 *  Created on: 05.03.2012
 *      Author: Tim
 */

#include "Map/Generator/Generator.h"

MapGenerator::MapGenerator() {
	// TODO Auto-generated constructor stub

}

MapGenerator::~MapGenerator() {
	// TODO Auto-generated destructor stub
}

bool MapGenerator::Init(Uint16  MinW, Uint16  MaxW, Uint16  MinH, Uint16  MaxH)
{
	//TODO: Maybe srand should be called from within Main::OnInit()
	srand(time(NULL));

	MapW = rand() % (MaxW - MinW + 1) + MinW;
	MapH = rand() % (MaxH - MinH + 1) + MinH;

	Rooms = new MG_Room[MapH * MapW];

	for(Uint16 Y=0;Y<MapH;Y++) {
		for(Uint16 X=0;X<MapW;X++) {
			unsigned char PossibleDoors = D_NONE;

			if(Y != 0) PossibleDoors |= D_TOP;
			if(Y != MapH - 1) PossibleDoors |= D_BOTTOM;
			if(X != 0) PossibleDoors |= D_LEFT;
			if(X != MapW - 1) PossibleDoors |= D_RIGHT;

			if(Rooms[Y * MapW + X].NumDoors() == 0 && PossibleDoors != 0) { //Doors can only be placed if there is a place for them to be
				eDirection Dir = Rooms[Y * MapW + X].GenerateDoors(PossibleDoors);

				Uint16 NextX = X;
				Uint16 NextY = Y;

				if(Dir == D_LEFT) {
					Dir = D_RIGHT;
					NextX -= 1;
				} else if(Dir == D_TOP) {
					Dir = D_BOTTOM;
					NextY -= 1;
				} else if(Dir == D_RIGHT) {
					Dir = D_LEFT;
					NextX += 1;
				} else if(Dir == D_BOTTOM) {
					Dir = D_TOP;
					NextY += 1;
				}

				Rooms[NextY * MapW + NextX].GenerateDoors(Dir);
			}

			if(Rooms[Y * MapW + X].NumDoors() < 2 && Rooms[Y * MapW + X].CanPlaceDoor(PossibleDoors)) {
				float P = (rand() % 1000) / 1000.0f;
				if(P > 0.60f) {
					eDirection Dir = Rooms[Y * MapW + X].GenerateDoors(PossibleDoors);

					Uint16 NextX = X;
					Uint16 NextY = Y;

					if(Dir == D_LEFT) {
						Dir = D_RIGHT;
						NextX -= 1;
					} else if(Dir == D_TOP) {
						Dir = D_BOTTOM;
						NextY -= 1;
					} else if(Dir == D_RIGHT) {
						Dir = D_LEFT;
						NextX += 1;
					} else if(Dir == D_BOTTOM) {
						Dir = D_TOP;
						NextY += 1;
					}

					Rooms[NextY * MapW + NextX].GenerateDoors(Dir);
				}
			}

			if(Rooms[Y * MapW + X].NumDoors() < 3 && Rooms[Y * MapW + X].CanPlaceDoor(PossibleDoors)) {
				float P = (rand() % 1000) / 1000.0f;
				if(P > 0.80f) {
					eDirection Dir = Rooms[Y * MapW + X].GenerateDoors(PossibleDoors);

					Uint16 NextX = X;
					Uint16 NextY = Y;

					if(Dir == D_LEFT) {
						Dir = D_RIGHT;
						NextX -= 1;
					} else if(Dir == D_TOP) {
						Dir = D_BOTTOM;
						NextY -= 1;
					} else if(Dir == D_RIGHT) {
						Dir = D_LEFT;
						NextX += 1;
					} else if(Dir == D_BOTTOM) {
						Dir = D_TOP;
						NextY += 1;
					}

					Rooms[NextY * MapW + NextX].GenerateDoors(Dir);
				}
			}

			//Generate Room Content
			float P = (rand() % 1000) / 1000.0f;
			if(P > 0.90f) {
				Rooms[Y * MapW + X].Content = RC_FARMLAND;
			} else if(P > 0.650f) {
				Rooms[Y * MapW + X].Content = RC_MONSTER;
			} else if(P > 0.40f) {
				Rooms[Y * MapW + X].Content = RC_LOOT;
			}
		}
	}
	return true;
}

void MapGenerator::Exit()
{
	delete[] Rooms;
}
