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
	else if(pEntity->IsPlayer())
		return HT_HOSTILE;
	else if(pEntity->EntityFlags.Is_Set(EF_MOB))
		return HT_FRIENDLY;
	else return HT_ITEM;
}

void CMobEntity::Attack(CMap* pMap, CEntity* pTarget)
{
	if(!IsPlayer()) {
		CWeaponType* pWeaponType = (CWeaponType*)CItemTypeList::GetType(ITL_MOBSTER_CLAW_WEAPON);
		if(Chance(pWeaponType->HitPercentage))
			pTarget->GetHurt(pWeaponType->Damage, pMap, this);
		else gMessages.AddFMessage("Der %s verfehlt dich", GetName());
	}

	if(!pTarget->IsPlayer()) {
		if(!pTarget->IsAlive(pMap)) {
			gMessages.AddFMessage("Der %s stirbt", pTarget->GetName());
			pMap->RemoveEntity(pMap->GetEntityId(pTarget));
		}
	}
}

Sint16 CMobEntity::GetHealth()
{
	return Health;
}

Sint16 CMobEntity::GetMaxHealth()
{
	return MaxHealth;
}

bool CMobEntity::IsAlive(CMap* pMap)
{
	return (Health > 0);
}

void CMobEntity::GetHurt(Uint8 Damage, CMap* pMap, CEntity* pAttacker)
{
	Health -= Damage;
	if(IsPlayer())
		gMessages.AddFMessage("Der %s atackiert dich mit %i Schadenspunkten", pAttacker->GetName(), Damage);
	else if(pAttacker->IsPlayer())
		gMessages.AddFMessage("Du atackierst den %s mit %i Schadenspunkten", GetName(), Damage);
	else
		gMessages.AddFMessage("Der %s atackiert den %s mit %i Schadenspunkten", pAttacker->GetName(), GetName(), Damage);
}

void CMobEntity::GetHealed(Uint8 Heal)
{
	if(Health < MaxHealth) {
		Health += Heal;
		if(Health > MaxHealth)
			Health = MaxHealth;
	}
}

const char* CMobEntity::GetName()
{
	return "Mobster";
}

const char* CMobEntity::GetDescription()
{
	return "Dieses Monster versucht dich zu toeten";
}

void CMobEntity::PickUp(CMap *pMap, CEntity *pItem)
{
	eItemType Type = pItem->GetItemType();
	if(Type == IT_NO_ITEM) return;

	eItemTypeList TypeId = pItem->GetItemTypeId(pMap);

	if(WieldedItem) Drop(pMap);

	pMap->RemoveEntity(pMap->GetEntityId(pItem));

	WieldedItem.New(Type);
	WieldedItem->TypeId = TypeId;
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
	if(WieldedItem->IsUseable() && ((CUseableItem*)(CItem*)WieldedItem)->Uses == 0)
		WieldedItem.Delete();
}

void CMobEntity::Tick(CMap* pMap)
{
	if(!IsPlayer())
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
