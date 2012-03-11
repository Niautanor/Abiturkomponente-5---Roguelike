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
		if(WieldedItem && WieldedItem->GetType() == IT_WEAPON)
			pTarget->GetHurt(3, pMap, this);
		else pTarget->GetHurt(1, pMap, this);
	} else {
		pTarget->GetHurt(2, pMap, this);
	}

	if(!pTarget->EntityFlags.Is_Set(EF_PLAYER)) {
		if(!pTarget->IsAlive(pMap)) {
			gMessages.AddFMessage("Der %s stirbt", pTarget->GetName());
			pMap->RemoveEntity(pMap->GetEntityId(pTarget));
		}
	}
}

bool CMobEntity::IsAlive(CMap* pMap)
{
	return (Health > 0);
}

void CMobEntity::GetHurt(Uint8 Damage, CMap* pMap, CEntity* pAttacker)
{
	Health -= Damage;
	if(EntityFlags.Is_Set(EF_PLAYER))
		gMessages.AddFMessage("Der %s atackiert dich mit %i Schadenspunkten", pAttacker->GetName(), Damage);
	else if(pAttacker->EntityFlags.Is_Set(EF_PLAYER))
		gMessages.AddFMessage("Du atackierst den %s mit %i Schadenspunkten", GetName(), Damage);
	else
		gMessages.AddFMessage("Der %s atackiert den %s mit %i Schadenspunkten", pAttacker->GetName(), GetName(), Damage);
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
	eItemType Type = pItem->GetItemType();
	if(Type == IT_NO_ITEM) return;

	Uint8 ExtraData = pItem->GetExtraData(pMap);

	if(WieldedItem) Drop(pMap);

	pMap->RemoveEntity(pMap->GetEntityId(pItem));

	WieldedItem.New(Type);
	WieldedItem->ExtraData = ExtraData;
}

void CMobEntity::Drop(CMap *pMap)
{
	if(!WieldedItem) return;

	pMap->AddEntity(new CItemEntity((CItem*)WieldedItem, Pos));

	WieldedItem.Delete();
}

bool CMobEntity::WieldsItem()
{
	return (bool)WieldedItem;
}

void CMobEntity::UseItem(CVector Dir, CMap* pMap)
{
	WieldedItem->OnUse(Pos + Dir, this, pMap);
	if(WieldedItem->Uses == 0)
		WieldedItem.Delete();
}

void CMobEntity::Tick(CMap* pMap)
{
	if(!EntityFlags.Is_Set(EF_PLAYER))
	{
		if(VectorLengthSq(Pos - pMap->GetPlayer()->Pos) <= 2) {
			Attack(pMap, pMap->GetPlayer());
		} else {
			Mov = pMap->GetPath(this, pMap->GetPlayer()->Pos);
			Uint8 NumTries = 0;
			if(Mov == CVector(0,0))
			{
				do {
					if(NumTries > 8) {
						Mov = CVector();
						break;
					}
					Mov = RandomVector(-1,-1,1,1);
					++NumTries;
				} while(Mov == CVector(0,0) || !CanMove(pMap, Mov));
			}
		}
	}
	CEntity::Tick(pMap);
}
