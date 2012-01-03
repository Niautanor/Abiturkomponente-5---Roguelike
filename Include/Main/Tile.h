/**
 * @class Tile
 * Speichert informationen zu
 */

#pragma once/* TILE_H_ */

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "HelperAPI/CColor.h"

class Tile
{
public:
	Tile();
	Tile(char Char, CColor fg, CColor bg);
	Tile(char Char, SDL_Color Fg, SDL_Color Bg) : C(Char), fg(Fg), bg(Bg) { }
	Uint16 C;//char
	SDL_Color fg;
	SDL_Color bg;

	void SetC(char Char);
	void SetFg(CColor Color);
	void SetBg(CColor Color);

	//Zeichnet das Zeichen an den angegebenen Koordinaten auf die angegeben Oberfläche
	bool DrawTile(SDL_Surface* pDisplay, TTF_Font* pFont, Uint32 XOffset, Uint32 YOffset, Uint32 TileWidth, Uint32 TileHeight);
};
