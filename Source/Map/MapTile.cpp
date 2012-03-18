/*
 * CMapTile.cpp
 *
 *  Created on: 21.09.2011
 *      Author: Tim
 */

#include "Map/MapTile.h"

CMapTile* CMapTile::EmptyTile = new CMapTile(Tile(' ', CL_BLACK, CL_BLACK), 0);
CMapTile* CMapTile::WallTile = new CMapTile(Tile('#', CL_GREEN, CL_BLACK), MTF_EXISTANT | MTF_VISIBLE);
CMapTile* CMapTile::GroundTile = new CMapTile(Tile('.', CL_WHITE, CL_BLACK), MTF_EXISTANT | MTF_VISIBLE | MTF_PASSABLE);

CMapTile* CMapTile::DoorTile = new CDoorTile(Tile(',', CColor(200,140,60), CL_BLACK), MTF_EXISTANT | MTF_VISIBLE | MTF_PASSABLE);

CMapTile* CMapTile::FarmTile = new CFarmTile(Tile('~', CColor(128, 64, 0), CL_BLACK), MTF_EXISTANT | MTF_VISIBLE | MTF_PASSABLE);

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
	PtrList<CEntity*> EntityList = pMap->GetTileEntityList(Pos);
	if(!EntityList.empty()) {
		ExamineEntitieList(EntityList);
		return;
	}

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
	if(!Flags.Is_Set(MTF_PASSABLE))
		return false;
	else {
		PtrList<CEntity*> EntityList = pMap->GetTileEntityList(Pos);
		for(Uint16 i=0;i<EntityList.size();i++) {
			if(EntityList[i] == pTrespasser)
				continue;
			if(EntityList[i]->EntityFlags.Is_Set(EF_MOB))
				return false;
		}
	}
	return true;
}

Tile CMapTile::GetTile(CVector Pos, CMap* pMap)
{
	PtrList<CEntity*> EntityList = pMap->GetTileEntityList(Pos);
	if(!EntityList.empty()) {
		if(ContainsPlayer(EntityList))
			return pMap->GetPlayer()->GetTile(pMap);
		else if(ContainsMobs(EntityList)) {
			PtrList<CEntity*> MobList = FilterMobEntities(EntityList);
			return MobList[0]->GetTile(pMap);
		} else
			return EntityList[0]->GetTile(pMap);
	}
	else return FloorTile;
}
