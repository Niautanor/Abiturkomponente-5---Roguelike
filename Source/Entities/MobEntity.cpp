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
		Mov = pMap->GetPath(this, pMap->GetPlayer()->Pos);
		if(Mov == CVector(0,0))
		{
			//TODO: add Random asdf movement
			do {
				Mov = RandomVector(-1,-1,1,1);
			} while(Mov == CVector(0,0));
		}
	}
	CEntity::Tick(pMap);
}
