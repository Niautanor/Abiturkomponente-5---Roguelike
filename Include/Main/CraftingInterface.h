/*
 * CraftingInterface.h
 *
 *  Created on: 01.03.2012
 *      Author: Tim
 */

#pragma once  /* CRAFTINGINTERFACE_H_ */

#include "Main/Screen.h"
#include "HelperAPI/CVector.h"
#include "Map/Map.h"

class CraftingInterface {
private:
	PtrList<CEntity*> MaterialList;
	bool Finished;

	Sint8 FirstChoice,SecondChoice;

	bool IsCombinable(CEntity* Item1, CEntity* Item2);

public:
	CraftingInterface();
	~CraftingInterface();

	bool Init(CVector UserPos, CMap* pMap);
	void Exit();

	void Render(Screen* MainScreen);
	void HandleDirectionKey(CVector Dir);
	void HandleKey(char Key);

	bool HasFinished();
};
