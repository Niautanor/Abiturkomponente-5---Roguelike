/*
 * Camera.h
 *
 *  Created on: 13.03.2012
 *      Author: Tim
 */

#pragma once  /* CAMERA_H_ */

#include <SDL/SDL_types.h>

#include "HelperAPI/CVector.h"

class CCamera {
private:
	Uint16 X, Y;
	Uint16 ScrW, ScrH;

public:
	CCamera();
	~CCamera();

	void Init(Uint16 VP_W, Uint16 VP_H);

	Uint16 GetX() { return X; }
	Uint16 GetY() { return Y; }
	Uint16 GetW() { return ScrW; }
	Uint16 GetH() { return ScrH; }

	void CenterCamera(const CVector& Pos, Uint16 MaxXpos, Uint16 MaxYpos);
};
