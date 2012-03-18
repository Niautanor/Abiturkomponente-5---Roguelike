/*
 * MapGenerator.cpp
 *
 *  Created on: 05.03.2012
 *      Author: Tim
 */

#include "Map/Generator/Generator.h"

MapGenerator::MapGenerator()
{
	// TODO Auto-generated constructor stub

}

MapGenerator::~MapGenerator()
{
	// TODO Auto-generated destructor stub
}

bool MapGenerator::Init(Uint16 MinW, Uint16 MaxW, Uint16 MinH, Uint16 MaxH)
{
	NumRoomsX = rand() % (MaxW - MinW + 1) + MinW;
	NumRoomsY = rand() % (MaxH - MinH + 1) + MinH;

	Rooms = new MG_Room[NumRoomsY * NumRoomsX];

	for(Uint16 Y = 0; Y < NumRoomsY; Y++) {
		for(Uint16 X = 0; X < NumRoomsX; X++) {
			unsigned char PossibleDoors = D_NONE;

			if(Y != 0)
				PossibleDoors |= D_TOP;
			if(Y != NumRoomsY - 1)
				PossibleDoors |= D_BOTTOM;
			if(X != 0)
				PossibleDoors |= D_LEFT;
			if(X != NumRoomsX - 1)
				PossibleDoors |= D_RIGHT;

			if(GetRoom(X, Y)->NumDoors() == 0 && PossibleDoors != 0) { //Doors can only be placed if there is a place for them to be
				eDirection Dir = GetRoom(X, Y)->GenerateDoors(PossibleDoors);

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

				GetRoom(NextX, NextY)->GenerateDoors(Dir);
			}

			if(GetRoom(X, Y)->NumDoors() < 2 && GetRoom(X, Y)->CanPlaceDoor(PossibleDoors)) {
				float P = (rand() % 1000) / 1000.0f;
				if(P > 0.60f) {
					eDirection Dir = GetRoom(X, Y)->GenerateDoors(PossibleDoors);

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

					GetRoom(NextX, NextY)->GenerateDoors(Dir);
				}
			}

			if(GetRoom(X, Y)->NumDoors() < 3 && GetRoom(X, Y)->CanPlaceDoor(PossibleDoors)) {
				float P = (rand() % 1000) / 1000.0f;
				if(P > 0.80f) {
					eDirection Dir = GetRoom(X, Y)->GenerateDoors(PossibleDoors);

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

					GetRoom(NextX, NextY)->GenerateDoors(Dir);
				}
			}

			//Generate Room Content
			float P = (rand() % 1000) / 1000.0f;
			if(P > 0.90f) {
				GetRoom(X, Y)->Content = RC_FARMLAND;
			} else if(P > 0.650f) {
				GetRoom(X, Y)->Content = RC_MONSTER;
			} else if(P > 0.40f) {
				GetRoom(X, Y)->Content = RC_LOOT;
			}
		}
	}

	//Map the Rooms to Tiles
	MapW = NumRoomsX * 4 + 1;
	MapH = NumRoomsY * 4 + 1;

	Tiles = new char[MapW * MapH];

	for(Uint16 X = 0; X < MapW; X++)
		GetTile(X, MapH - 1) = '#';
	for(Uint16 Y = 0; Y < MapH; Y++)
		GetTile(MapW - 1, Y) = '#';

	for(Uint16 Y = 0; Y < NumRoomsY; Y++) {
		for(Uint16 X = 0; X < NumRoomsX; X++) {

			for(Uint8 Yp = 0; Yp < 4; Yp++) {
				for(Uint8 Xp = 0; Xp < 4; Xp++) {
					Uint16 Yr = Y * 4 + Yp; //Rendered Y coordinate
					Uint16 Xr = X * 4 + Xp; //Rendered X

					char TileToBePlaced = '.';

					if(Yp == 0 || Xp == 0) { //Wall or Door
						if(Xp == 2 && GetRoom(X, Y)->Doors[1]) //N/S Door & Doors[1] -> TopDoor
							TileToBePlaced = '+';
						else if(Yp == 2 && GetRoom(X, Y)->Doors[0]) //W/E Door & Doors[0] -> Left Door
							TileToBePlaced = '+';
						else //Wall
						TileToBePlaced = '#';
					}

					GetTile(Xr, Yr) = TileToBePlaced;
				}
			}

			CVector ContentPos = RandomVector(X * 4 + 1, Y * 4 + 1, X * 4 + 3, Y * 4 + 3); //The Floor Tiles of the Room
			switch(GetRoom(X, Y)->Content) {
			case RC_FARMLAND:
				GetTile(ContentPos.X, ContentPos.Y) = '~';
				break;
			case RC_LOOT:
				GetTile(ContentPos.X, ContentPos.Y) = ':';
				break;
			case RC_MONSTER:
				GetTile(ContentPos.X, ContentPos.Y) = '&';
				break;
			default:
				//GetTile(ContentPos.X, ContentPos.Y) = '.';
				break;
			}

		}
	}

	return true;
}

void MapGenerator::Exit()
{
	delete[] Rooms;
	delete[] Tiles;
}
