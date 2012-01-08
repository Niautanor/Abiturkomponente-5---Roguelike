/*
 * DoorTile.cpp
 *
 *  Created on: 03.01.2012
 *      Author: Tim
 */

#include "Map/DoorTile.h"

void CDoorTile::OnInteract(CVector Pos, CMap* pMap, CEntity* pActor)
{
	FlagSet<Uint8>& TileData = pMap->GetTileData(Pos);
	if(TileData.Is_Set(DTD_OPEN))
	{
		if(pActor->Pos == Pos) {
			gMessages.AddMessage("Du kannst kein Tor schließen, auf dem du stehst");
			return;
		}
		else if(!pMap->GetTileEntityList(Pos).empty()) {
			gMessages.AddMessage("Du kannst kein Tor schließen, auf dem etwas steht");
			return;
		}
		TileData.Unset(DTD_OPEN);
	}
	else
	{
		TileData.Set(DTD_OPEN);
	}
}

void CDoorTile::OnExamine(CVector Pos, CMap* pMap, CEntity* pActor)
{
	if(pMap->GetTileData(Pos).Is_Set(DTD_OPEN)) gMessages.AddMessage("Dies ist eine offenes Tor");
	else gMessages.AddMessage("Dieses Tor ist geschlossen");
}

bool CDoorTile::IsPassable(CVector Pos, CMap* pMap, CEntity* pTrespasser)
{
	bool Open = pMap->GetTileData(Pos).Is_Set(DTD_OPEN);
	bool TilePassable = CMapTile::IsPassable(Pos, pMap, pTrespasser);
	return (Open && TilePassable);
}

Tile CDoorTile::GetTile(CVector Pos, CMap* pMap)
{
	if(pMap->GetTileData(Pos).Is_Set(DTD_OPEN))
		return CMapTile::GetTile(Pos, pMap);
	else return Tile('+', FloorTile.fg, FloorTile.bg);
}
