/*
 * Main_UserAction.cpp
 *
 *  Created on: 15.09.2011
 *      Author: Tim
 */

#include "Main/Main.h"

Uint16 Main::GetUserAction(SDL_Event* pEvent)
{
	while(SDL_WaitEvent(pEvent))
	{
		switch(pEvent->type)
		{
		case SDL_QUIT:
			Finished = true;
			return 0;
		case SDL_KEYDOWN:
			switch(pEvent->key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return 'q';
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
			break;//disables a unhelpfull eclipse Warning
		}
	}

	return 0;
}

void Main::HandleDirectionKey(CVector Dir)
{
	if(InputMode == IM_MAIN)
	{
		if(Map.GetEntity(PlayerEntity)->CanMove(&Map, Dir)) {
			Map.GetEntity(PlayerEntity)->Mov += Dir;
			PendingTicks++;
		}
		else gMessages.AddMessage("Boing!");
	}
	else if(InputMode == IM_EXAMINE) {
		Map.GetTile(Map.GetEntity(PlayerEntity)->Pos + Dir)->OnExamine(Map.GetEntity(PlayerEntity)->Pos + Dir, &Map, Map.GetEntity(PlayerEntity));
		InputMode = IM_MAIN;
	}
	else if(InputMode == IM_INTERACT) {
		Map.GetTile(Map.GetEntity(PlayerEntity)->Pos + Dir)->OnInteract(Map.GetEntity(PlayerEntity)->Pos + Dir, &Map, Map.GetEntity(PlayerEntity));
		InputMode = IM_MAIN;
	}
}

void Main::HandleUserAction(Uint16 c)
{
	switch(c)
	{
	case 'Q':
		Finished = true;
		break;
	case 'q':
		GameMode = GM_MAIN;
		InputMode = IM_MAIN;
		break;
	case '1':
		HandleDirectionKey(CVector(-1,1));
		break;
	case '3':
		HandleDirectionKey(CVector(1,1));
		break;
	case '7':
		HandleDirectionKey(CVector(-1,-1));
		break;
	case '9':
		HandleDirectionKey(CVector(1,-1));
		break;
	case '2':
		HandleDirectionKey(CVector(0,1));
		break;
	case '4':
		HandleDirectionKey(CVector(-1,0));
		break;
	case '5'://'5' -> warten
		HandleDirectionKey(CVector(0,0));
		break;
	case '6':
		HandleDirectionKey(CVector(1,0));
		break;
	case '8':
		HandleDirectionKey(CVector(0,-1));
		break;
	case 'm':
		if(GameMode == GM_MESSAGE_ARCHIVE)
			GameMode = GM_MAIN;
		else
			GameMode = GM_MESSAGE_ARCHIVE;
		break;
	case 'i':
		if(InputMode != IM_MAIN)
			break;
		InputMode = IM_INTERACT;
		gMessages.AddMessage("Interaktionsmodus: ('q' zum Beenden)");
		break;
	case 'e':
		if(InputMode != IM_MAIN)
			break;
		InputMode = IM_EXAMINE;
		gMessages.AddMessage("Untersuchungsmodus ('q' zum Beenden)");
		break;
	case 'c':
		gMessages.Clear();
		break;
	case 't':
		PendingTicks++;
		break;
	case 'h':
		gMessages.AddMessage("TASTE FUER HALLO GEDRUECKT! ASDFL");
		break;
	}
}
