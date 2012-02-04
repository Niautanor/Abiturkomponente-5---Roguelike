/*
 * MobEntity.cpp
 *
 *  Created on: 07.01.2012
 *      Author: Tim
 */

#include "Entities/MobEntity.h"

Uint8 CMobEntity::IsHostile(CEntity *pEntity)
{
	if(pEntity == this)
		return HT_NONE;
	else if(pEntity->EntityFlags.Is_Set(EF_PLAYER))
		return HT_HOSTILE;
	else if(pEntity->EntityFlags.Is_Set(EF_MOB))
		return HT_FRIENDLY;
	else return HT_ITEM;
}

void CMobEntity::Attack(CMap* pMap, CEntity* pTarget)
{
	if(EntityFlags.Is_Set(EF_PLAYER)) {
		gMessages.AddFMessage("Du Attackierst den %s", pTarget->GetName());
	} else {
		gMessages.AddFMessage("The %s glares at you", GetName());
	}
}

const char* CMobEntity::GetName()
{
	if(EntityFlags.Is_Set(EF_PLAYER))
		return "Du selbst";
	return "Mobster";
}

void CMobEntity::Tick(CMap* pMap)
{
	if(!EntityFlags.Is_Set(EF_PLAYER))
	{
		if(VectorLengthSq(Pos - pMap->GetPlayer()->Pos) <= 2) { //Attack TODO: Add Actual Attack Code
			Attack(pMap, pMap->GetPlayer());
		} else {
			Mov = pMap->GetPath(this, pMap->GetPlayer()->Pos);
			if(Mov == CVector(0,0))
			{
				do {
					Mov = RandomVector(-1,-1,1,1);
				} while(Mov == CVector(0,0) || !CanMove(pMap, Mov)); //TODO: Fix potential Problem with wich the entity could get Stuck in an endless loop if it can move nowhere
			}
		}
	}
	CEntity::Tick(pMap);
}
