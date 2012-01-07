/*
 * CMap.cpp
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#include "Map/Map.h"

CMap::CMap()
{
	MapWidth = MapHeight = 0;
	TileList.clear();
}

bool CMap::OnInit(Uint16 Width, Uint16 Height)
{
	if(!Width || !Height)
		return false;
	MapWidth = Width;
	MapHeight = Height;

	TileList.clear();
	for(Uint32 i=0;i<(MapHeight*MapWidth);i++)
		TileList.Push(CMapTile::EmptyTile);

	TileDataList = new FlagSet<Uint8>[MapWidth * MapHeight];
	for(Uint16 i=0;i<(MapWidth*MapHeight);i++)
		TileDataList[i].Clear();

	EntityList.clear();

	return true;
}

void CMap::OnExit()
{
	for(Uint32 i=0;i<EntityList.size();i++)
		EntityList.Remove(i);
	EntityList.clear();

	delete[] TileDataList;

	for(Uint32 i=0;i<TileList.size();i++)
		TileList[i] = NULL;//Tiles sind keine eigenständigen Objekte und können deshalb nich gelöscht werden
	TileList.clear();
}

/**
 * @function:
 * Zeichnet ein Feld auf den Screenbuffer
 *
 * @origin:
 * Ursprünglich aus der Funktion DrawMap()
 **/
bool CMap::DrawTile(Screen* s, Uint16 X, Uint16 Y, Uint16 StartX, Uint16 StartY)
{
	if(!(X < MapWidth || Y < MapHeight)) return false;

	if(TileList[Y*MapWidth+X]->Flags.Is_Set(MTF_EXISTANT) && TileList[Y*MapWidth+X]->Flags.Is_Set(MTF_VISIBLE))
		if(!(s->Put(TileList[Y*MapWidth+X]->GetTile(CVector(X, Y), this), StartX+X, StartY+Y)))
			return false;
	return true;
}

/**
 * @function:
 * Gibt eine Liste mit allen das Feld besetzenden Entitys zurück
 **/
PtrList<CEntity*> CMap::GetTileEntityList(CVector Pos)
{
	PtrList<CEntity*> ReturnList;
	for(Uint32 i=0;i<EntityList.size();i++)
		if(EntityList[i]->Pos == Pos)
			ReturnList.Push(EntityList[i]);
	return ReturnList;
}

/**
 * @function:
 * Extradaten eines Tiles
 **/
FlagSet<Uint8>& CMap::GetTileData(CVector Pos)
{
	return TileDataList[Pos.Y*MapWidth+Pos.X];
}

/**
 * @function:
 * primitiver Pathfinding algorythmus
 **/
CVector CMap::GetPath(CEntity* pEntity, CVector Target)
{
	if(pEntity->Pos == Target)
		return CVector(0,0);

	Sint16 X=0, Y=0;

	if(pEntity->Pos.X < Target.X) X = 1;
	else if(pEntity->Pos.X > Target.X) X = -1;

	if(pEntity->Pos.Y < Target.Y) Y = 1;
	else if(pEntity->Pos.Y > Target.Y) Y = -1;

	if(pEntity->CanMove(this, CVector(X, Y)))
		return CVector(X, Y);
	else if(Y != 0 && pEntity->CanMove(this, CVector(0, Y)))
		return CVector(0, Y);
	else if(X != 0 && pEntity->CanMove(this, CVector(X, 0)))
		return CVector(X, 0);

	return CVector(0,0);
}

/**
 * @function:
 * Gibt die Spieler-Entity zurück
 **/
CEntity* CMap::GetPlayer()
{
	for(Uint32 i=0;i<EntityList.size();i++)
	{
		if(EntityList[i] && EntityList[i]->EntityFlags.Is_Set(EF_PLAYER))
			return EntityList[i];
	}
	return NULL;
}

void CMap::Tick()
{
	for(Uint32 Y=0;Y<MapHeight;Y++)
		for(Uint32 X=0;X<MapWidth;X++)
			if(TileList[Y*MapWidth+X])
				TileList[Y*MapWidth+X]->Tick(CVector(X,Y), this);
	for(Uint32 i=0;i<EntityList.size();i++)
		if(EntityList[i])
			EntityList[i]->Tick(this);
}

/**
 * @function:
 * Füllt die gesamte Map mit dem Angegebenen Feld
 *
 * @ClearTile:
 * Das Feld, auf das jedes Feld der Map gesetzt werden soll
 **/
void CMap::ClearMap(CMapTile* ClearTile)
{
	for(Uint16 Y=0;Y<MapHeight;Y++)
		for(Uint16 X=0;X<MapWidth;X++)
			TileList[Y*MapWidth+X] = ClearTile;
}

/**
 * @function:
 * Zeichnet die Karte auf das angegebene Screen Objekt
 *
 * @s:
 * screenbuffer
 *
 * @StartX, StartY:
 * An diesen Koordinaten wird das Linke Obere Feld gezeichnet werden
 * (Alle anderen breiten sich nach Rechtsunten aus)
 **/
bool CMap::DrawMap(Screen* s, Uint16 StartX, Uint16 StartY)
{
	if(!s) return false;

	bool ret = true;
	for(Uint16 Y=0;Y<MapHeight;Y++)
		for(Uint16 X=0;X<MapWidth;X++)
			if(!DrawTile(s,X,Y,StartX,StartY))
				ret = false;
	return ret;
}

/**
 * @function:
 * Setzt das Feld mit den angegebenen Koordinaten auf T
 *
 * @T:
 * Tile
 *
 * @X,Y:
 * Koordinaten
 **/
void CMap::PutMapTile(CMapTile* T, Uint16 X, Uint16 Y)
{
	if(!(X >= MapWidth || Y >= MapHeight))
	{
		TileList[Y*MapWidth+X] = T;
	}
}

CMapTile*& CMap::GetTile(CVector Pos)
{
		if(Pos.X < MapWidth && Pos.Y < MapHeight)
			return TileList[Pos.Y*MapWidth+Pos.X];
		else return CMapTile::EmptyTile;
}

void CMap::AddEntity(CEntity* pEntity)
{
	if(pEntity)//If there is an Entity to be pushed
		EntityList.Push(pEntity);
}

void CMap::RemoveEntity(CEntity* pEntity)
{
	if(pEntity)
		EntityList.Remove(pEntity);
}
