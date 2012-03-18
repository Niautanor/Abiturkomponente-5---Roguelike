/*
 * CMap.h
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#pragma once/* CMAP_H_ */

class CMap;

#include "Map/Generator/Generator.h"

#include "Main/Screen.h"
#include "HelperAPI/CVector.h"

#include "HelperAPI/PtrList.h"

#include "Map/MapTile.h"
#include "Entities/Entity.h"

#include "Entities/EntityListFilter.h"

class CMap
{
private:
	Uint16 MapWidth, MapHeight;

	PtrList<CMapTile*> TileList; //TileList ist eine Pointerliste OHNE Objektkontrolle(automatisches delete), da die Eigenschaften der Spielfelder in globalen Pointern festgelegt werden. Sie dürfen nicht gelöscht werden
	PtrList<CEntity*> EntityList;
	FlagSet<Uint8>* TileDataList;//Enthält Informationen zu Positionsspezifischen Tile-Eigenschaften(offene Türen, versteckte Fallen, usw)

	bool* FOV_Map;

	/*Refractored from DrawMap*/
	bool DrawTile(Screen* s, Uint16 X, Uint16 Y, Uint16 StartX, Uint16 StartY);

public:
	CMap();

	CMapTile*& GetTile(CVector Pos);

	//Fügt eine Entity zur Liste hinzu und gibt ihre ID zurück
	int AddEntity(CEntity* pEntity);
	void RemoveEntity(int Id);
	int GetEntityId(CEntity* pEntity);

	CEntity* GetEntity(int Id);

	Uint16 GetW() { return MapWidth; }
	Uint16 GetH() { return MapHeight; }

	/*Init und Exit*/
	bool OnInit(Uint16 Width, Uint16 Height);
	bool InitWithGenerator(Uint16 MinW, Uint16 MinH, Uint16 MaxW, Uint16 MaxH);
	void OnExit();

	//Gibt eine Liste mit allen Entities auf einem Feld zurück
	PtrList<CEntity*> GetTileEntityList(CVector Pos);

	//Returns the combined TileEntityList of all Surrounding Tiles
	PtrList<CEntity*> GetAllEntitiesInProximity(CVector Pos);

	//Gibt eine Referenz auf die Tile-Daten eines Feldes zurück
	FlagSet<Uint8>& GetTileData(CVector Pos);

	//Berechnet eine Pfad von einer Entity zu einem Punkt
	CVector GetPath(CEntity* pEntity, CVector Target);

	//Gibt einen Zeiger auf die erste(die auch die einzige sein sollte) Entity mit EF_PLAYER zurück
	CEntity* GetPlayer();

	//Bewegt alle Tiles und Entities
	void Tick();

	void Recalculate_FOV(CVector PlayerPos);
	bool IsInFOV(CVector Pos);

	/*Grundsätzliche Verwaltungsfunktionen*/
	void ClearMap(CMapTile* ClearTile);
	bool DrawMap(Screen* s, Uint16 StartX, Uint16 StartY, Uint16 VP_X = 0, Uint16 VP_Y = 0, Uint16 VP_W = 0, Uint16 VP_H = 0);
	void PutMapTile(CMapTile* T, Uint16 X, Uint16 Y);
};
