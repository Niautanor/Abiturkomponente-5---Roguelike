/*
 * Main_UserAction.cpp
 *
 *  Created on: 15.09.2011
 *      Author: Tim
 */

#include "Main/Main.h"

Uint16 Main::GetUserAction(SDL_Event* pEvent)
{
	while(SDL_WaitEvent(pEvent)) {
		switch(pEvent->type) {
		case SDL_QUIT:
			Finished = true;
			return 0;
		case SDL_KEYDOWN:
			switch(pEvent->key.keysym.sym) {
			case SDLK_RSHIFT:
			case SDLK_LSHIFT:
				continue;
			case SDLK_ESCAPE:
				return 'q';
			case SDLK_RETURN:
				return 'y';
			case SDLK_UP:
				return '8';
			case SDLK_DOWN:
				return '2';
			case SDLK_LEFT:
				return '4';
			case SDLK_RIGHT:
				return '6';
			default:
				return pEvent->key.keysym.unicode;
			}
			break; //disables a unhelpfull eclipse Warning
		}
	}

	return 0;
}

void Main::HandleDirectionKey(CVector Dir)
{
	switch(GameMode) {
	case GM_MAIN:
		if(InputMode == IM_MAIN) //Movement/attack or wait(5)
				{
			if(Dir == CVector(0, 0)) {
				//Wait
				PendingTicks++;
				return;
			}

			PtrList<CEntity*> EntityList = Map.GetTileEntityList(Map.GetEntity(PlayerEntity)->Pos + Dir);
			PtrList<CEntity*> HostileList = FilterHostility(EntityList, Map.GetEntity(PlayerEntity), HT_HOSTILE);
			if(!HostileList.empty()) {
				if(HostileList.size() == 1) {
					if(Question("Willst du den Gegner auf diesem Feld angreifen?")) {
						Map.GetEntity(PlayerEntity)->Attack(&Map, HostileList[0]);
						PendingTicks++;
					}
				} else {
					Uint8 choice = ListQuestion("Was Angreifen?", HostileList);
					Map.GetEntity(PlayerEntity)->Attack(&Map, HostileList[choice]);
					PendingTicks++;
				}
				return;

			}

			if(Map.GetEntity(PlayerEntity)->CanMove(&Map, Dir)) {
				Map.GetEntity(PlayerEntity)->Mov += Dir;
				PendingTicks++;
			} else gMessages.AddMessage("Boing!");
		} else if(InputMode == IM_EXAMINE) {
			Map.GetTile(Map.GetEntity(PlayerEntity)->Pos + Dir)->OnExamine(Map.GetEntity(PlayerEntity)->Pos + Dir, &Map, Map.GetEntity(PlayerEntity));
			InputMode = IM_MAIN;
		} else if(InputMode == IM_INTERACT) {
			Map.GetTile(Map.GetEntity(PlayerEntity)->Pos + Dir)->OnInteract(Map.GetEntity(PlayerEntity)->Pos + Dir, &Map, Map.GetEntity(PlayerEntity));

			if(Map.GetTile(Map.GetEntity(PlayerEntity)->Pos + Dir) == CMapTile::DoorTile)//A door was opened
				Map.Recalculate_FOV(Map.GetEntity(PlayerEntity)->Pos + Dir*2);

			InputMode = IM_MAIN;
		} else if(InputMode == IM_USE) {
			Map.GetEntity(PlayerEntity)->UseItem(Dir, &Map);
			InputMode = IM_MAIN;
		}
		break;
	case GM_MESSAGE_ARCHIVE:
		break;
	/*case GM_CRAFTING:
		Crafting.HandleDirectionKey(Dir);
		break;*/
	default:
		break;
	}
}

void Main::HandleUserAction(Uint16 c)
{
	switch(c) {
	case 'Q':
		Finished = true;
		return;
	case 'q':
		GameMode = GM_MAIN;
		InputMode = IM_MAIN;
		return;
	case '1':
		HandleDirectionKey(CVector(-1, 1));
		return;
	case '3':
		HandleDirectionKey(CVector(1, 1));
		return;
	case '7':
		HandleDirectionKey(CVector(-1, -1));
		return;
	case '9':
		HandleDirectionKey(CVector(1, -1));
		return;
	case '2':
		HandleDirectionKey(CVector(0, 1));
		return;
	case '4':
		HandleDirectionKey(CVector(-1, 0));
		return;
	case '5': //'5' -> warten
		HandleDirectionKey(CVector(0, 0));
		return;
	case '6':
		HandleDirectionKey(CVector(1, 0));
		return;
	case '8':
		HandleDirectionKey(CVector(0, -1));
		return;
	}

	//Case Specific Key handling
	switch(GameMode) {
	case GM_MAIN:
		switch(c) {
		case 'm':
			GameMode = GM_MESSAGE_ARCHIVE;
			break;
		case 'i':
			InputMode = IM_INTERACT;
			gMessages.AddMessage("Interaktionsmodus: ('q' zum Beenden)");
			break;
		case 'e':
			InputMode = IM_EXAMINE;
			gMessages.AddMessage("Untersuchungsmodus ('q' zum Beenden)");
			break;
		case 'u':
			if(!Map.GetEntity(PlayerEntity)->WieldsItem()) {
				gMessages.AddMessage("Du haeltst nichts in der Hand");
				break;
			}
			if(!((CPlayer*)Map.GetEntity(PlayerEntity))->WieldedItem->RequiresDirection())
				Map.GetEntity(PlayerEntity)->UseItem(CVector(0,0), &Map);
			else InputMode = IM_USE;
			break;
		/*case '&':
			GameMode = GM_CRAFTING;
			if(!Crafting.Init(Map.GetEntity(PlayerEntity)->Pos, &Map)) {
				gMessages.AddMessage("Crafting.Init schlug fehl");
				GameMode = GM_MAIN;
			}
			break;*/
		case 'g': { //Pick up
			PtrList<CEntity*> ItemList = FilterItems(Map.GetTileEntityList(Map.GetEntity(PlayerEntity)->Pos));
			switch(ItemList.size()) {
			case 0:
				return;
			case 1:
				Map.GetEntity(PlayerEntity)->PickUp(&Map, ItemList[0]);
				break;
			default:
				Uint8 Choice = ListQuestion("Was willst du aufnehmen?", ItemList);
				Map.GetEntity(PlayerEntity)->PickUp(&Map, ItemList[Choice]);
				break;
			}
			break;
		}
		case 'd':
			Map.GetEntity(PlayerEntity)->Drop(&Map);
			break;
		/*case 's': { //Spawn Seed
			const char* Names[] = { "Plumphelmet", "Spinecrawler", "Banelingplant" };

			eItemTypeList ItemTypeId;
			Uint8 Choice = ListQuestion("ASDF?", CreateNameList(3, Names));

			switch(Choice) {
			case 0:
				ItemTypeId = ITL_PLUMPHELMET_SEED;
				break;
			case 1:
				ItemTypeId = ITL_SPINECRAWLER_SEED;
				break;
			case 2:
				ItemTypeId = ITL_BANELING_SEED;
				break;
			}
			Map.AddEntity(new CItemEntity(IT_SEED, ItemTypeId, Map.GetEntity(PlayerEntity)->Pos));
			break;
		}*/
		case 'c':
			gMessages.Clear();
			break;
		case 't':
			PendingTicks++;
			break;
		/*case 'h':
			gMessages.AddMessage("TASTE FUER HALLO GEDRUECKT! ASDFL");
			break;*/
		}
		break;
	case GM_DEAD:
		if(c == 'y') {
			Map.OnExit();
			gMessages.Clear();
			Map.InitWithGenerator(6,4,12,8);
			PlayerEntity = Map.AddEntity(new CPlayer(Tile('@', CColor(200,0,200), CColor(0,0,0)), CVector(1,1), EF_MOB, 15, 25));
			Camera.CenterCamera(Map.GetEntity(PlayerEntity)->Pos, Map.GetW(), Map.GetH());
			Map.Recalculate_FOV(Map.GetEntity(PlayerEntity)->Pos);
			GameMode = GM_MAIN;
		}
		break;
	/*case GM_CRAFTING:
		Crafting.HandleKey(c);
		if(Crafting.HasFinished()) {
			Crafting.Exit();
			GameMode = GM_MAIN;
		}
		break;*/
	case GM_MESSAGE_ARCHIVE:
		GameMode = GM_MAIN;
		break;
	default:
		break;
	}
}
