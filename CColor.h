/**
 * @file CColor.h
 *
 * enth�lt
 * @class CColor
 * Klasse f�r einfachere Farbangaben
 */

#pragma once/* CCOLOR_H_ */

#include <SDL/SDL.h>

class CColor
{
public:
	Uint8 r, g, b;

	CColor() { }
	CColor(Uint8 cr, Uint8 cg, Uint8 cb) : // Initialisierungsliste
		r(cr), g(cg), b(cb)
	{
	}

	//CColor() -> SDL_Color(r, g, b); weil casting operatoren irgendwie nicht so toll �berladbar waren
	SDL_Color operator () ()
	{
		SDL_Color ret = { r, g, b };
		return ret;
	}
};
