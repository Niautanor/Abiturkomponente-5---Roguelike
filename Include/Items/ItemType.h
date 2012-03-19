/*
 * ItemType.h
 *
 *  Created on: 19.03.2012
 *      Author: Tim
 */

#pragma once  /* ITEMTYPE_H_ */

#include "HelperAPI/PtrList.h"

#include <string>

enum eItemType {
	IT_NO_ITEM = 0,
	IT_WEAPON,
	IT_SEED,
	IT_POTION
};

enum eItemExtraData {
	IED_NONE = 0,
	//if(Type == IT_SEED)
	SIED_PLUMPHELMET = 0x20,//Seed Item Extra Data
	SIED_SPINECRAWLER = 0x30,
	SIED_BANELING = 0x40,
	SIED_MOBSTERPLANT = 0x50,
	SIED_CANCER_CURE = 0x60
};

enum eItemTypeList {
	ITL_NONE = 0,
	ITL_PLUMPHELMET_SEED,
	ITL_SPINECRAWLER_SEED,
	ITL_BANELING_SEED,
	ITL_FIST_WEAPON,
	ITL_MOBSTER_CLAW_WEAPON,
	ITL_SHARP_SWORD_WEAPON,
	ITL_SMALL_POTION,
	ITL_BIG_POTION
};

struct CItemType {
	CItemType(std::string N, std::string D) : Name(N), Description(D) { }
	virtual ~CItemType() { }

	std::string Name;
	std::string Description;

	virtual bool IsUsable() { return false; }
};

struct CUseableType : public CItemType {
	CUseableType(Uint8 uses, std::string N, std::string D) : CItemType(N, D), default_uses(uses) { }

	Uint8 default_uses;

	virtual bool IsUsable() { return true; }
};

struct CSeedType : public CUseableType {
	eItemExtraData SeedType;

	CSeedType(eItemExtraData  SType, std::string N, std::string D) : CUseableType(1, N, D), SeedType(SType) { }
};

struct CWeaponType : public CItemType {
	Uint8 Damage;
	Uint8 HitPercentage;

	CWeaponType(Uint8 Damage_, Uint8 HitPercentage_, std::string N, std::string D) : CItemType(N, D), Damage(Damage_), HitPercentage(HitPercentage_) { }
};

struct CPotionType : public CUseableType {
	Uint8 Heal;

	CPotionType(Uint8 Heal_, std::string N, std::string D) : CUseableType(1, N, D), Heal(Heal_) { }
};

class CItemTypeList {
private:
	static PtrList<CItemType*> TypeList;

public:
	static bool InitTypes();
	static void ExitTypes();

	static CItemType* GetType(eItemTypeList Id);
};
