/*
 * CMapTile.cpp
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#include "Map/MapTile.h"

CMapTile* CMapTile::EmptyTile = new CMapTile(Tile(' ', CColor(0,0,0), CColor(0,0,0)), 0);
CMapTile* CMapTile::WallTile = new CMapTile(Tile('#', CColor(0,255,0), CColor(0,0,0)), MTF_EXISTANT | MTF_VISIBLE);
CMapTile* CMapTile::GroundTile = new CMapTile(Tile('.', CColor(255,255,255), CColor(0,0,0)), MTF_EXISTANT | MTF_VISIBLE | MTF_PASSABLE);

CMapTile* CMapTile::DoorTile = new CDoorTile(Tile(',', CColor(0,255,0), CColor(0,0,0)), MTF_EXISTANT | MTF_VISIBLE);

CMapTile::CMapTile(Tile t, MapTileFlag Flagset)
{
	FloorTile = t;

	this->Flags.Clear();
	this->Flags.Set(Flagset);
}

void CMapTile::OnInteract(CVector Pos, CMap* pMap, CEntity* pActor)
{
	gMessages.AddMessage("Du kannst hier nichts tun!");
}

void CMapTile::OnExamine(CVector Pos, CMap* pMap, CEntity* pActor)
{
	if(this == EmptyTile) {
		gMessages.AddMessage("Du schaust in die Weiten des Weltraums WTF!");
		return;
	}
	if(!Flags.Is_Set(MTF_PASSABLE))
		gMessages.AddMessage("Du schaust auf ein Stueck feste Wand");
	else gMessages.AddMessage("Du kannst dich hier hinbewegen");
}

void CMapTile::Tick(CVector Pos, CMap* pMap)
{

}

bool CMapTile::IsPassable(CVector Pos, CMap* pMap, CEntity* pTrespasser)
{
	return Flags.Is_Set(MTF_PASSABLE);
}

Tile CMapTile::GetTile(CVector Pos, CMap* pMap)
{
	PtrList<CEntity*> EntityList = pMap->GetTileEntityList(Pos);
	if(!EntityList.empty())
		return EntityList[0]->GetTile(pMap);
	else return FloorTile;
}
