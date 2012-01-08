/*
 * Random.cpp
 *
 *  Created on: 08.01.2012
 *      Author: Tim
 */

#include "HelperAPI/Random.h"

bool Init_Random()
{
	srand(time(NULL));
	return true;
}

CVector RandomVector(Sint16 MinX, Sint16 MinY, Sint16 MaxX, Sint16 MaxY)
{
	Sint16 X_range = MaxX - MinX + 1;
	Sint16 Y_range = MaxY - MinY + 1;

	Sint16 X = rand() % X_range + MinX;
	Sint16 Y = rand() % Y_range + MinY;

	return CVector(X, Y);
}


