/*
 * Screen.h
 *
 *  Created on: 15.09.2011
 *      Author: Tim
 */

#pragma once/* SCREEN_H_ */

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Tile.h"

class Screen
{
private:
	Uint16 TileHeight, TileWidth;
	Uint16 NumRows, NumCols;

	//Ein Array aus Unicode-Chars
	Tile** Tiles;

public:
	Screen();

	bool OnInit(Uint16 TileHeight, Uint16 TileWidth, Uint16 NumRows, Uint16 NumCols);
	void OnExit();

	//Ein Zeichen auf den Bildshirm Setzen
	bool Put(Tile T, Uint16 X, Uint16 Y);
	//Einen Text auf den Bildschirm Setzen
	bool PutText(Uint16* Text, CColor Fg, CColor Bg, Uint16 X, Uint16 Y);

	bool Render(SDL_Surface* pDisplay, TTF_Font* pFont);//Zeichnet alle {Chars} aur den Bildschirm
	bool ClearScreen();//Setzt alle Chars auf Char(0, SDL_COLOR(0,0,0), SDL_COLOR(0,0,0))

};
