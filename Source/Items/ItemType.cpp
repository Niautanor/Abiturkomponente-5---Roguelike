/*
 * ItemType.cpp
 *
 *  Created on: 19.03.2012
 *      Author: Tim
 */

#include "Items/ItemType.h"

PtrList<CItemType*> CItemTypeList::TypeList;

bool CItemTypeList::InitTypes()//IMPORTANT: To Long Descriptions will result in a segfault when examining
{
	TypeList.Push(new CItemType("", ""));//ITL_NONE

	TypeList.Push(new CSeedType(SIED_PLUMPHELMET, "Plump Samen", "Der Samen eines beliebten Nahrungsmittels"));//ITL_PLUMPHELMET_SEED
	TypeList.Push(new CSeedType(SIED_SPINECRAWLER, "Spine Samen", "Der Samen einer Pflanze, die sich zu wehren weiss"));//ITL_SPINECRAWLER_SEED
	TypeList.Push(new CSeedType(SIED_BANELING, "Baneling Samen", "Der Samen einer Pflanze mit Heilender Wirkung"));//ITL_BANELING_SEED

	TypeList.Push(new CWeaponType(2, 50, "Deine Faust", "Das sollte niemals zu sehen sein"));//ITL_FIST_WEAPON
	TypeList.Push(new CWeaponType(2,65, "Mobster Klauen", "Das sollte niemals zu sehen sein"));//ITL_MOBSTER_CLAWS_WEAPON
	TypeList.Push(new CWeaponType(5, 80, "Schwert", "Scharfes Schwert"));//ITL_SHARP_SWORD_WEAPON

	TypeList.Push(new CPotionType(4, "Heiltrank(Kl)", "Kleiner Heiltrank"));//ITL_SMALL_POTION
	TypeList.Push(new CPotionType(8, "Heiltrank(Gr)", "Großer Heiltrank"));//ITL_BIG_POTION

	return true;
}

void CItemTypeList::ExitTypes()
{
	if(!TypeList.empty())
		TypeList.OnExit();
}

CItemType* CItemTypeList::GetType(eItemTypeList Id)
{
	if(Id >= TypeList.size())
		throw "ItemtType Zugriffsverletzung";
	return TypeList[Id];
}
