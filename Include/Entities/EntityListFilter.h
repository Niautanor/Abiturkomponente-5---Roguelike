/*
 * EntityListFilter.h
 *
 *  Created on: 21.01.2012
 *      Author: Tim
 */

#pragma once  /* ENTITYLISTFILTER_H_ */

#include "Entities/Entity.h"

#include "HelperAPI/PtrList.h"

PtrList<CEntity*> FilterMobEntities(PtrList<CEntity*>& EntityList);

PtrList<CEntity*> FilterHostility(PtrList<CEntity*>& EntityList, CEntity* pPOVEntity, eHostilityType Hostility);

PtrList<CEntity*> FilterItems(PtrList<CEntity*>& EntityList);

void ExamineEntitieList(PtrList<CEntity*>& EntityList);
