/*
 * DoorTile.cpp
 *
 *  Created on: 03.01.2012
 *      Author: Tim
 */

#include "Map/DoorTile.h"

void CDoorTile::OnInteract(CVector Pos, CMap* pMap, CEntity* pActor)
{
	if(Open)
	{
		Open = false;
		Flags.Unset(MTF_PASSABLE);
	}
	else
	{
		Open = true;
		Flags.Set(MTF_PASSABLE);
	}
}

void CDoorTile::OnExamine(CVector Pos, CMap* pMap, CEntity* pActor)
{
	if(Open) gMessages.AddMessage("Dies ist eine offenes Tor");
	else gMessages.AddMessage("Dieses Tor ist geschlossen");
}

Tile CDoorTile::GetTile(CVector Pos, CMap* pMap)
{
	if(Open) return CMapTile::GetTile(Pos, pMap);
	else return Tile('+', FloorTile.fg, FloorTile.bg);
}
