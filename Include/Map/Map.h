/*
 * CMap.h
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#pragma once/* CMAP_H_ */

class CMap;

#include "Main/Screen.h"
#include "HelperAPI/CVector.h"

#include "HelperAPI/PtrList.h"

#include "Map/MapTile.h"
#include "Entities/Entity.h"

class CMap
{
private:
	Uint16 MapWidth, MapHeight;

	PtrList<CMapTile*> TileList; //TileList ist eine Pointerliste OHNE Objektkontrolle(automatisches delete), da die Eigenschaften der Spielfelder in globalen Pointern festgelegt werden. Sie dürfen nicht gelöscht werden
	PtrList<CEntity*> EntityList;
	FlagSet<Uint8>* TileDataList;//Enthält Informationen zu Positionsspezifischen Tile-Eigenschaften(offene Türen, versteckte Fallen, usw)

	/*Refractored from DrawMap*/
	bool DrawTile(Screen* s, Uint16 X, Uint16 Y, Uint16 StartX, Uint16 StartY);

public:
	CMap();

	CMapTile*& GetTile(CVector Pos);

	void AddEntity(CEntity* pEntity);
	void RemoveEntity(CEntity* pEntity);

	Uint16 GetW() { return MapWidth; }
	Uint16 GetH() { return MapHeight; }

	/*Init und Exit*/
	bool OnInit(Uint16 Width, Uint16 Height);
	void OnExit();

	//Gibt eine Liste mit allen Entities auf einem Feld zurück
	PtrList<CEntity*> GetTileEntityList(CVector Pos);

	//Gibt eine Referenz auf die Tile-Daten eines Feldes zurück
	FlagSet<Uint8>& GetTileData(CVector Pos);

	//Bewegt alle Tiles und Entities
	void Tick();

	/*Grundsätzliche Verwaltungsfunktionen*/
	void ClearMap(CMapTile* ClearTile);
	bool DrawMap(Screen* s, Uint16 StartX, Uint16 StartY);
	void PutMapTile(CMapTile* T, Uint16 X, Uint16 Y);
};
