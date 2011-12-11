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

bool Tile::DrawTile(SDL_Surface* pDisplay, TTF_Font* pFont, Uint32 XOffset, Uint32 YOffset, Uint32 TileWidth, Uint32 TileHeight)
{
	SDL_Surface* pGlyph = TTF_RenderGlyph_Shaded(pFont, C, fg, bg); //Zeichnet das Zeichen des Tiles auf pGlyph
	if(!pGlyph)
		return false;

	SDL_Surface* pTile = SDL_CreateRGBSurface(SDL_HWSURFACE, TileWidth, TileHeight, 8, pGlyph->format->Rmask, pGlyph->format->Gmask, pGlyph->format->Bmask, pGlyph->format->Amask);
	if(!pTile)
		return false;
	SDL_SetColors(pTile, pGlyph->format->palette->colors, 0, pGlyph->format->palette->ncolors);//Die Farben von pGlyph importieren
	SDL_FillRect(pTile, NULL, 0);//0 ist die Hintergrundfarbe von pGlyph

	SDL_Rect TileRc;
	TileRc.x = (TileWidth / 2) - (pGlyph->w / 2);
	TileRc.y = TileHeight - pGlyph->h;

	SDL_BlitSurface(pGlyph, NULL, pTile, &TileRc);//Die Oberfläche pTile enthält jetzt den Glyph mit füllender Hintergrundfarbe

	SDL_FreeSurface(pGlyph);

	SDL_Rect DisplayRc;
	DisplayRc.x = XOffset;
	DisplayRc.y = YOffset;

	SDL_BlitSurface(pTile, NULL, pDisplay, &DisplayRc);//pTile befindet sich jetzt auf dem Bildschirm

	SDL_FreeSurface(pTile);

	return true;
}
