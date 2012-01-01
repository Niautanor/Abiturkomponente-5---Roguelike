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

void Main::HandleUserAction(Uint16 c)
{
	switch(c)
	{
	case 'Q':
		Finished = true;
		break;
	case '1':
		if(pPlayer->CanMove(&Map, CVector(-1,1))) {
			pPlayer->Mov += CVector(-1,1);
			PendingTicks++;
		}
		else Messages.AddMessage("Boing!");
		break;
	case '3':
		if(pPlayer->CanMove(&Map, CVector(1,1))) {
			pPlayer->Mov += CVector(1,1);
			PendingTicks++;
		}
		else Messages.AddMessage("Boing!");
		break;
	case '7':
		if(pPlayer->CanMove(&Map, CVector(-1,-1))) {
			pPlayer->Mov += CVector(-1,-1);
			PendingTicks++;
		}
		else Messages.AddMessage("Boing!");
		break;
	case '9':
		if(pPlayer->CanMove(&Map, CVector(1,-1))) {
			pPlayer->Mov += CVector(1,-1);
			PendingTicks++;
		}
		else Messages.AddMessage("Boing!");
		break;
	case '2':
		if(pPlayer->CanMove(&Map, CVector(0,1))) {
			pPlayer->Mov += CVector(0,1);
			PendingTicks++;
		}
		else Messages.AddMessage("Boing!");
		break;
	case '4':
		if(pPlayer->CanMove(&Map, CVector(-1,0))) {
			pPlayer->Mov += CVector(-1,0);
			PendingTicks++;
		}
		else Messages.AddMessage("Boing!");
		break;
	case '6':
		if(pPlayer->CanMove(&Map, CVector(1,0))) {
			pPlayer->Mov += CVector(1,0);
			PendingTicks++;
		}
		else Messages.AddMessage("Boing!");
		break;
	case '8':
		if(pPlayer->CanMove(&Map, CVector(0,-1))) {
			pPlayer->Mov += CVector(0,-1);
			PendingTicks++;
		}
		else Messages.AddMessage("Boing!");
		break;
	case 'm':
		if(GameMode == GM_MESSAGE_ARCHIVE)
			GameMode = GM_MAIN;
		else
			GameMode = GM_MESSAGE_ARCHIVE;
		break;
	case 'c':
		Messages.Clear();
		break;
	case 't':
		PendingTicks++;
		break;
	case 'h':
		Messages.AddMessage("TASTE FUER HALLO GEDRUECKT! ASDFL");
		break;
	case 'l':
		Messages.AddMessage("LOLSCHOCK!");
		break;
	}
}
