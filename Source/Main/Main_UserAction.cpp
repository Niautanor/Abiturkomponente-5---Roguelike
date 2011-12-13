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
		}
	}

	return 0;
}

void Main::HandleUserAction(Uint16 c)
{
	switch(c)
	{
	case 'Q':
		Finished = true;
		break;
	case '1':
		AtY++;
		AtX--;
		if(Map.GetTile((AtX-2)%Map.GetW(), (AtY-6)%Map.GetH())->Flags.Is_Set(MTF_PASSABLE)) {
			AtY--;
			AtX++;
		}
		break;
	case '3':
		AtY++;
		AtX++;
		break;
	case '7':
		AtY--;
		AtX--;
		break;
	case '9':
		AtY--;
		AtX++;
		break;
	case '2':
		AtY++;
		break;
	case '4':
		AtX--;
		break;
	case '6':
		AtX++;
		break;
	case '8':
		AtY--;
		break;
	case 'c':
		Messages.Clear();
		break;
	case 'h':
		Messages.AddMessage("TASTE FUER HALLO GEDRUECKT! ASDFL");
		break;
	}
}
