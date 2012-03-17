/*
 * Player.h
 *
 *  Created on: 12.03.2012
 *      Author: Tim
 */

#pragma once  /* PLAYER_H_ */

#include "Entities/MobEntity.h"

class CPlayer : public CMobEntity {
public:
	CPlayer(Tile T = Tile('M', CColor(255,0,0), CColor(0,0,0)), CVector Position = CVector(1,1), Uint8 Flags = EF_MOB, Uint8 Initial_Health = 5) : CMobEntity(T, Position, Flags, Initial_Health) { }
	~CPlayer() { }

	const char* GetName() const;
	const char* GetDescription() const;

	bool IsPlayer();

	void Attack(CMap* pMap, CEntity* pTarget);
};
