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

const char* CMobEntity::GetDescription()
{
	if(EntityFlags.Is_Set(EF_PLAYER))
		return "Du bist ein Geiler Abenteurer";
	return "Dieses Monster versucht dich zu toeten";
}

void CMobEntity::PickUp(CMap *pMap, CEntity *pItem)
{
	eItemType Type = pItem->GetItemType(pMap);
	if(Type == IT_NO_ITEM) return;
	if(WieldedItem) Drop(pMap);

	pMap->RemoveEntity(pMap->GetEntityId(pItem));

	WieldedItem.New();
	WieldedItem->Type = Type;
}

void CMobEntity::Drop(CMap *pMap)
{
	if(!WieldedItem) return;

	eItemType Type = WieldedItem->Type;
	WieldedItem.Delete();
	int ItemEntity = pMap->AddEntity(new CItemEntity(Tile('i', CColor(0,0,255), CColor(0,0,0)), Pos));
	pMap->GetEntity(ItemEntity)->SetItemType(Type);
}

bool CMobEntity::WieldsItem()
{
	return (bool)WieldedItem;
}

void CMobEntity::UseItem(CVector Dir, CMap* pMap)
{
	WieldedItem->OnUse(Pos + Dir, this, pMap);
}

void CMobEntity::Tick(CMap* pMap)
{
	if(!EntityFlags.Is_Set(EF_PLAYER))
	{
		if(VectorLengthSq(Pos - pMap->GetPlayer()->Pos) <= 2) {
			Attack(pMap, pMap->GetPlayer());
		} else {
			Mov = pMap->GetPath(this, pMap->GetPlayer()->Pos);
			if(Mov == CVector(0,0))
			{
				do {
					Mov = RandomVector(-1,-1,1,1);
				} while(Mov == CVector(0,0) || !CanMove(pMap, Mov)); //FIXME: Fix potential Problem with wich the entity could get Stuck in an endless loop if it can move nowhere
			}
		}
	}
	CEntity::Tick(pMap);
}
