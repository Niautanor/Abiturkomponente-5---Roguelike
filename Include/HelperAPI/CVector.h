/**
 * @file: CVector.h
 * Definiert eine Klasse für Vektoren und Positionsangaben
 *
 *  Created on: 20.10.2011
 *      Author: Tim
 **/

#pragma once /* CVECTOR_H_ */

class CVector
{
public:
	Sint16 X,Y;

	CVector() : X(0), Y(0) { }
	CVector(const CVector& v) : X(v.X), Y(v.Y) { }
	CVector(const signed short vX, const signed short vY) : X(vX), Y(vY) { }

	CVector& operator = (const CVector& v)
	{
		X = v.X;
		Y = v.Y;

		return *this;
	}

	CVector& operator += (const CVector& v)
	{
		X += v.X;
		Y += v.Y;

		return *this;
	}

	CVector& operator -= (const CVector& v)
	{
		X -= v.X;
		Y -= v.Y;

		return *this;
	}

	Uint16 LengthSq() const//LengthSquared
	{
		return (X*X+Y*Y);
	}
};

inline bool operator == (const CVector& a, const CVector& b)
{
	return (a.X == b.X && a.Y == b.Y);
}

inline bool operator != (const CVector& a, const CVector& b)
{
	return (a.X != b.X || a.Y != b.Y);
}

inline Uint16 VectorLengthSq(const CVector& v)
{
	return v.LengthSq();
}

inline CVector operator + (const CVector& a, const CVector& b)
{
	return CVector(a.X+b.X, a.Y+b.Y);
}

inline CVector operator - (const CVector& a, const CVector& b)
{
	return CVector(a.X-b.X, a.Y-b.Y);
}
