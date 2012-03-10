/*
 * Screen.h
 *
 *  Created on: 15.09.2011
 *      Author: Tim
 */

#pragma once/* SCREEN_H_ */

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Main/Tile.h"

class Screen
{
private:
	Uint16 TileHeight, TileWidth;
	Uint16 NumRows, NumCols;

	//Ein Array aus Unicode-Chars
	Tile** Tiles;

public:
	Screen();

	Uint16 W() { return NumCols; }
	Uint16 H() { return NumRows; }
	Tile GetTile(Uint16 X, Uint16 Y);

	bool OnInit(Uint16 TileHeight, Uint16 TileWidth, Uint16 NumRows, Uint16 NumCols);
	void OnExit();

	//Ein Zeichen auf den Bildshirm Setzen
	bool Put(Tile T, Uint16 X, Uint16 Y);
	//Einen Text auf den Bildschirm Setzen
	bool PutText(char* Text, CColor Fg, CColor Bg, Uint16 X, Uint16 Y);
	//Setzt einen Vorformatierten Text auf den Bildschirm
	bool PutFText(CColor Fg, CColor Bg, Uint16 X, Uint16 Y, Uint16 BufferSize, const char* Format, ...);
	//Zeichnet eine anderen Bildschirm auf diesen
	bool PutScreen(Screen* pScren, Uint16 X, Uint16 Y, Uint16 SrcX=0, Uint16 SrcY=0, Uint16 W=0, Uint16 H=0);

	bool Render(SDL_Surface* pDisplay, TTF_Font* pFont);//Zeichnet alle {Chars} aur den Bildschirm
	bool ClearScreen();//Setzt alle Chars auf Char(0, SDL_COLOR(0,0,0), SDL_COLOR(0,0,0))

};
