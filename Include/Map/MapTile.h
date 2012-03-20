/*
 * CMapTile.h
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#pragma once/* CMAPTILE_H_ */

class CMapTile;

#include "HelperAPI/FlagSet.h"

#include "Main/Tile.h"

#include "Map/Map.h"

#include "HelperAPI/PtrList.h"
#include "Entities/Entity.h"

#include "CMessageQueue.h"

typedef Uint16 MapTileFlag;

enum eMapTileFlags
{
	MTF_EXISTANT = 0x0001,
	MTF_VISIBLE = 0x0002,
	MTF_PASSABLE = 0x0004
};

class CMapTile
{
protected:
	Tile FloorTile;

public:
	CMapTile() : FloorTile(Tile(' ',CColor(0,0,0),CColor(255,255,255))) { Flags.Clear(); }
	CMapTile(Tile t, MapTileFlag Flagset);

	virtual ~CMapTile() { };

	static CMapTile* EmptyTile;
	static CMapTile* WallTile;
	static CMapTile* GroundTile;
	static CMapTile* ExitTile;

	static CMapTile* DoorTile;

	static CMapTile* FarmTile;

	FlagSet<Uint16> Flags;

	virtual void Tick(CVector Pos, CMap* pMap);

	/**
	 * @function: Erlaubt dem Spieler mit einem Stück der welt zu interagieren
	 **/
	virtual void OnInteract(CVector Pos, CMap* pMap, CEntity* pActor);

	/**
	 * @function: Zeigt eine Statusnachricht für ein Tile an
	 */
	virtual void OnExamine(CVector Pos, CMap* pMap, CEntity* pActor);

	/**
	 * @function: Legt fest, ob ein Feld von der Entity pTrespasser betreten werden kann
	 * @default: wenn das Flag MTF_PASSABLE gesetzt ist
	 **/
	virtual bool IsPassable(CVector Pos, CMap* pMap, CEntity* pTrespasser);

	/**
	 * @function: Returns the drawable colored Character of the mapTile
	 * by default the FloorTile
	 * which can be replaced by Entitys on the Tile
	 **/
	virtual Tile GetTile(CVector Pos, CMap* pMap);
};

//somehow this needs to be at the end
#include "Map/DoorTile.h"//Have all the Tiletypes in one spot(as static members of CMapTile)
#include "Map/FarmTile.h"
