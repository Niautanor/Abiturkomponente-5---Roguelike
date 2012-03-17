/*
 * MobEntity.cpp
 *
 *  Created on: 07.01.2012
 *      Author: Tim
 */

#include "Entities/MobEntity.h"

const SmartObjectList<CItem>& CMobEntity::GetInventory()
{
	return Inventory;
}

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
	if(!IsPlayer())
		pTarget->GetHurt(2, pMap, this);

	if(!pTarget->IsPlayer()) {
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
	if(IsPlayer())
		gMessages.AddFMessage("Der %s atackiert dich mit %i Schadenspunkten", pAttacker->GetName(), Damage);
	else if(pAttacker->IsPlayer())
		gMessages.AddFMessage("Du atackierst den %s mit %i Schadenspunkten", GetName(), Damage);
	else gMessages.AddFMessage("Der %s atackiert den %s mit %i Schadenspunkten", pAttacker->GetName(), GetName(), Damage);
}

const char* CMobEntity::GetName() const
{
	return "Mobster";
}

const char* CMobEntity::GetDescription() const
{
	return "Dieses Monster versucht dich zu toeten";
}

void CMobEntity::PickUp(CMap* pMap, CEntity* pItem)
{
	eItemType Type = pItem->GetItemType();
	if(Type == IT_NO_ITEM)
		return;

	Uint8 ExtraData = pItem->GetExtraData(pMap);

	pMap->RemoveEntity(pMap->GetEntityId(pItem));

	Inventory[Inventory.Push(Type)]->ExtraData = ExtraData; //l33t h4x
	//equals: Uint32 Id = Inventory.Push(Type); Inventory[Id]->ExtraData = ExtraData
}

void CMobEntity::Drop(CMap* pMap, Uint8 InventoryId)
{
	if(InventoryId >= Inventory.size() || !Inventory[InventoryId])
		return;

	pMap->AddEntity(new CItemEntity(Inventory[InventoryId], Pos));

	Inventory.Delete(InventoryId);
}

void CMobEntity::WieldItem(CMap* pMap, Uint8 InventoryId)
{
	if(InventoryId >= Inventory.size() || !Inventory[InventoryId]) {
		gMessages.AddMessage("Du besitzt diesen Gegenstand nicht");
		return;
	}

	if(WieldsItem())
		UnwieldItem(pMap);

	WieldedItem.New(Inventory[InventoryId]->GetType());
	WieldedItem->ExtraData = Inventory[InventoryId]->ExtraData;

	Inventory.Delete(InventoryId);
}

void CMobEntity::UnwieldItem(CMap* pMap)
{
	if(!WieldedItem) {
		gMessages.AddMessage("Du hälst nichts in der Hand");
		return;
	}

	Inventory[Inventory.Push(WieldedItem->GetType())]->ExtraData = WieldedItem->ExtraData;	//3v3n m0r3 h4x
	WieldedItem.Delete();
}

bool CMobEntity::WieldsItem()
{
	return WieldedItem;
}

void CMobEntity::UseItem(CVector Dir, CMap* pMap)
{
	WieldedItem->OnUse(Pos + Dir, this, pMap);
	if(WieldedItem->Uses == 0)
		WieldedItem.Delete();
}

void CMobEntity::Tick(CMap* pMap)
{
	if(!IsPlayer()) {
		if(VectorLengthSq(Pos - pMap->GetPlayer()->Pos) <= 2) {
			Attack(pMap, pMap->GetPlayer());
		} else {
			Mov = pMap->GetPath(this, pMap->GetPlayer()->Pos);
			Uint8 NumTries = 0;
			if(Mov == CVector(0, 0)) {
				do {
					if(NumTries > 8) {
						Mov = CVector();
						break;
					}
					Mov = RandomVector(-1, -1, 1, 1);
					++NumTries;
				} while(Mov == CVector(0, 0) || !CanMove(pMap, Mov));
			}
		}
	}
	CEntity::Tick(pMap);
}
