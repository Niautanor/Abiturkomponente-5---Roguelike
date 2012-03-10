/*
 * EntityListFilter.cpp
 *
 *  Created on: 21.01.2012
 *      Author: Tim
 */

#include "Entities/EntityListFilter.h"

PtrList<CEntity*> FilterMobEntities(PtrList<CEntity*>& EntityList)
{
	PtrList<CEntity*> ReturnList;
	for (Uint16 i = 0; i < EntityList.size(); i++) {
		if (EntityList[i] && EntityList[i]->EntityFlags.Is_Set(EF_MOB))
			ReturnList.Push(EntityList[i]);
	}
	return ReturnList;
}

PtrList<CEntity*> FilterHostility(PtrList<CEntity*>& EntityList, CEntity* pPOVEntity, eHostilityType Hostility)
{
	PtrList<CEntity*> ReturnList;
	for (Uint16 i = 0; i < EntityList.size(); i++) {
		if (EntityList[i] && (EntityList[i]->IsHostile(pPOVEntity) == Hostility))
			ReturnList.Push(EntityList[i]);
	}
	return ReturnList;
}

PtrList<CEntity*> FilterItems(PtrList<CEntity*>& EntityList)
{
	PtrList<CEntity*> ReturnList;
	for(Uint16 i = 0; i < EntityList.size();i++){
		if(EntityList[i] && (EntityList[i]->GetItemType() != IT_NO_ITEM))
			ReturnList.Push(EntityList[i]);
	}
	return ReturnList;
}

void ExamineEntitieList(PtrList<CEntity*>& EntityList)
{
	if (!EntityList.empty()) {
		if (EntityList.size() == 1) {
			gMessages.AddFMessage("%s - %s", EntityList[0]->GetName(),
					EntityList[0]->GetDescription());
		} else {
			gMessages.AddMessage("Es sind mehrere Objekte hier:");
			for (Uint16 i = 0; i < EntityList.size(); i++) {
				gMessages.AddFMessage(" %c - %s", 'a' + i, EntityList[i]->GetName());
			}
		}
	}
}
