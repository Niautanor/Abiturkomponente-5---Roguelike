/**
 * @file: CVector.h
 * Definiert eine Klasse für Vektoren und Positionsangaben
 *
 *  Created on: 20.10.2011
 *      Author: Tim
 **/

#pragma once/* CVECTOR_H_ */

class CVector
{
public:
	unsigned short X,Y;

	CVector() { X = Y = 0; }
	CVector(CVector& v) : X(v.X), Y(v.Y) { }
	CVector(unsigned short vX, unsigned short vY) : X(vX), Y(vY) { }
};
