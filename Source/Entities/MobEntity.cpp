/*
 * MobEntity.cpp
 *
 *  Created on: 07.01.2012
 *      Author: Tim
 */

#include "Entities/MobEntity.h"

void CMobEntity::Tick(CMap* pMap)
{
	if(!EntityFlags.Is_Set(EF_PLAYER))
	{
		if(VectorLengthSq(Pos - pMap->GetPlayer()->Pos) <= 2) { //Attack TODO: Add Actual Attack Code
			gMessages.AddMessage("Du wirst vom Puscheldaemon angeschaut!");
		} else {
			Mov = pMap->GetPath(this, pMap->GetPlayer()->Pos);
			if(Mov == CVector(0,0))
			{
				do {
					Mov = RandomVector(-1,-1,1,1);
				} while(Mov == CVector(0,0) || !CanMove(pMap, Mov));
			}
		}
	}
	CEntity::Tick(pMap);
}
