/*
 * CraftingInterface.cpp
 *
 *  Created on: 01.03.2012
 *      Author: Tim
 */

#include "Main/CraftingInterface.h"

CraftingInterface::CraftingInterface()
{
	Finished = true;
}

CraftingInterface::~CraftingInterface()
{
}

bool CraftingInterface::IsCombinable(CEntity* Item1, CEntity* Item2)
{
	if(Item1->GetItemType() == IT_SEED || Item2->GetItemType() == IT_SEED)
		return false;

	return true;
}

bool CraftingInterface::Init(CVector UserPos, CMap* pMap)
{
	//TODO: Filter to display only Materials
	MaterialList = pMap->GetAllEntitiesInProximity(UserPos);
	MaterialList = FilterItems(MaterialList);

	Finished = false;

	FirstChoice = SecondChoice = -1;

	return true;
}

void CraftingInterface::Exit()
{
	MaterialList.clear();
}

void CraftingInterface::Render(Screen* MainScreen)
{
	MainScreen->PutText((char*) "Crafting : q zum beenden", CColor(255, 255, 255), CColor(0, 0, 0), 0, 0);
	MainScreen->PutText((char*) "a-z zum auswaehlen von Items in der Liste", CColor(255, 255, 255), CColor(0, 0, 0), 0, 1);

	for(Uint16 i = 0; i < MaterialList.size(); i++) {
		MainScreen->PutFText(CColor(255, 255, 255), (FirstChoice == i || SecondChoice == i) ? CColor(66, 66, 66) : CColor(0, 0, 0), 0, 2 + i, 30, "%c - %s",i + 'a', MaterialList[i]->GetName());
	}
}

void CraftingInterface::HandleDirectionKey(CVector Dir)
{
}

void CraftingInterface::HandleKey(char Key)
{
	switch(Key) {
	case 'q':
		Finished = true;
		break;
	case 'y':
		if((FirstChoice != -1 && SecondChoice != -1) && IsCombinable(MaterialList[FirstChoice], MaterialList[SecondChoice])) {
			gMessages.AddMessage("Die beiden gegenstaende sind kombinierbar");
			Finished = true;
		}
		break;
	}
	if(Key >= 'a' && Key <= 'z') {
		if(FirstChoice == Key - 'a')
			FirstChoice = -1;
		else if(SecondChoice == Key - 'a')
			SecondChoice = -1;
		else if(FirstChoice == -1 && (Key - 'a') < MaterialList.size() && MaterialList[Key - 'a'])
			FirstChoice = Key - 'a';
		else if(SecondChoice == -1 && (Key - 'a') < MaterialList.size() && MaterialList[Key - 'a'])
			SecondChoice = Key - 'a';
	}
}

bool CraftingInterface::HasFinished()
{
	return Finished;
}

