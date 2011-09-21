/*
 * Screen.cpp
 *
 *  Created on: 15.09.2011
 *      Author: Tim
 */

#include "Screen.h"

Screen::Screen()
{
	TileWidth = TileHeight = 0;
	NumRows = NumCols = 0;
}

bool Screen::OnInit(Uint16 TileHeight, Uint16 TileWidth, Uint16 NumRows, Uint16 NumCols)
{
	this->TileHeight = TileHeight;
	this->TileWidth = TileWidth;
	this->NumRows = NumRows;
	this->NumCols = NumCols;

	Tiles = new Tile*[NumRows];
	for(int i=0;i<NumRows;i++)
		Tiles[i] = new Tile[NumCols];

	return (Tiles != NULL);
}

void Screen::OnExit()
{
	for(int i=0;i<NumRows;i++)
		delete[] Tiles[i];
	delete[] Tiles;
}

bool Screen::Put(Tile T, Uint16 X, Uint16 Y)
{
	if(X >= NumCols || Y >= NumRows)
		return false;

	Tiles[Y][X] = T;

	return true;
}

bool Screen::PutText(Uint16* Text, CColor Fg, CColor Bg, Uint16 X, Uint16 Y)
{
	int i = 0;
	while(Text[i])
	{
		if(!Put(Tile(Text[i], Fg, Bg), X+i, Y))
			return false;
		i++;
	}
	return true;
}

bool Screen::ClearScreen()
{
	for(Uint16 Y=0;Y<NumRows;Y++)
		for(Uint16 X=0;X<NumCols;X++)
			if(!Put(Tile(0,CColor(0,0,0),CColor(0,0,0)), X, Y))
				return false;
	return true;
}

bool Screen::Render(SDL_Surface* pDisplay, TTF_Font* pFont)
{
	for(Uint16 Y=0;Y<NumRows;Y++)
		for(Uint16 X=0;X<NumCols;X++)
			if(!Tiles[Y][X].DrawTile(pDisplay, pFont, TileWidth * X, TileHeight * Y, TileWidth, TileHeight))
				return false;
	return true;
}
