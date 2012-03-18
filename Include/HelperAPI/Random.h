/*
 * Random.h
 *
 *  Created on: 08.01.2012
 *      Author: Tim
 */

#pragma once  /* RANDOM_H_ */

#include <stdlib.h>
#include <time.h>

#include<SDL/SDL_types.h>

#include "HelperAPI/CVector.h"

bool Init_Random();

CVector RandomVector(Sint16 MinX, Sint16 MinY, Sint16 MaxX, Sint16 MaxY);

bool Chance(Uint8 Percentage);
