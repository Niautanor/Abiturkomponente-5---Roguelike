/**
 * @file CColor.h
 *
 * enthält
 * @class CColor
 * Klasse für einfachere Farbangaben
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

	//CColor() -> SDL_Color(r, g, b); weil casting operatoren irgendwie nicht so toll überladbar waren
	SDL_Color operator () ()
	{
		SDL_Color ret = { r, g, b };
		return ret;
	}
};

const CColor CL_BLACK = CColor(0,0,0);
const CColor CL_WHITE = CColor(255,255,255);
const CColor CL_RED = CColor(255,0,0);
const CColor CL_GREEN = CColor(15,235,15);
const CColor CL_BLUE = CColor(0,0,255);
