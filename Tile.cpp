/*
 * Tile.cpp
 *
 *  Created on: 15.09.2011
 *      Author: Tim
 */

#include "Tile.h"

Tile::Tile()
{
	C = 0;
	fg = (CColor(0,0,0))();
	bg = (CColor(0,0,0))();
}

Tile::Tile(Uint16 Char, CColor foreground, CColor background)
{
	C = Char;
	fg = foreground();
	bg = background();
}

void Tile::SetC(Uint16 Char)
{
	C = Char;
}

void Tile::SetFg(CColor Color)
{
	fg = Color();
}

void Tile::SetBg(CColor Color)
{
	bg = Color();
}

bool Tile::DrawTile(SDL_Surface* pDisplay, TTF_Font* pFont, Uint32 XOffset, Uint32 YOffset)
{
	SDL_Surface* pTile = TTF_RenderGlyph_Shaded(pFont, C, fg, bg);
	if(!pTile) return false;

	SDL_Rect rc;
	rc.x = XOffset;
	rc.y = YOffset;

	SDL_BlitSurface(pTile, NULL, pDisplay, &rc);

	SDL_FreeSurface(pTile);

	return true;
}
