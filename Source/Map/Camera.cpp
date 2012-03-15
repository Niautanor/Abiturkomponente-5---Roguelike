/*
 * Camera.cpp
 *
 *  Created on: 13.03.2012
 *      Author: Tim
 */

#include "Map/Camera.h"

CCamera::CCamera()
{
	X = Y = ScrW = ScrH = 0;
}

CCamera::~CCamera()
{
}

/**
 * @function:
 * Initialisiert einen Viewport für die Kamera
 *
 * @param VP_W, VP_H:
 * Höhe und Breite des Viewports
 **/
void CCamera::Init(Uint16 VP_W, Uint16 VP_H)
{
	ScrW = VP_W;
	ScrH = VP_H;
}

/**
 * @function:
 * Zentriert die Kamera auf eine gegebene Position
 *
 * @param MaxXpos, MaxYpos:
 * Maximale Koordinaten des rechtesten und tiefsten Feldes das gezeichnete werden soll
 **/
void CCamera::CenterCamera(const CVector& Pos, Uint16 MaxXpos, Uint16 MaxYpos)
{
	if(ScrW / 2 + Pos.X >= MaxXpos)
		if(ScrW > MaxXpos)
			X = 0;
		else X = MaxXpos - ScrW;
	else if(ScrW / 2 < Pos.X)
		X = Pos.X - ScrW / 2;
	else X = 0;

	if(ScrH / 2 + Pos.Y >= MaxYpos)
		if(ScrH > MaxYpos)
			Y = 0;
		else Y = MaxYpos - ScrH;
	else if(ScrH / 2 < Pos.Y)
		Y = Pos.Y - ScrH / 2;
	else Y = 0;
}

