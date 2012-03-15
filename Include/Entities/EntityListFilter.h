/*
 * EntityListFilter.h
 *
 *  Created on: 21.01.2012
 *      Author: Tim
 */

#pragma once  /* ENTITYLISTFILTER_H_ */

#include "Entities/Entity.h"

#include "HelperAPI/PtrList.h"

bool ContainsPlayer(const PtrList<CEntity*>& EntityList);

bool ContainsMobs(const PtrList<CEntity*>& EntityList);

bool ContainsItems(const PtrList<CEntity*>& EntityList);

PtrList<CEntity*> FilterMobEntities(const PtrList<CEntity*>& EntityList);

PtrList<CEntity*> FilterHostility(const PtrList<CEntity*>& EntityList, CEntity* pPOVEntity, eHostilityType Hostility);

PtrList<CEntity*> FilterItems(const PtrList<CEntity*>& EntityList);

void ExamineEntitieList(const PtrList<CEntity*>& EntityList);
