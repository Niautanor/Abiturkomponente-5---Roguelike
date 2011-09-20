/*
 * Unicode.h
 *
 *  Created on: 20.09.2011
 *      Author: Tim
 */

#pragma once/* UNICODE_H_ */

#include <cstring>

#include <SDL/SDL.h>

//Typdefinition für Unicode Strings
typedef Uint16        UNICODE_CHAR;
typedef UNICODE_CHAR* UNICODE_STRING;

//Casting Methode für Unicode Strings (ACHTUNG: erzeugt mit new Neue Speicherlecks ( -> Delete[])
UNICODE_STRING TextToUnicode(const char* Text);
UNICODE_STRING UnicodeCpy(UNICODE_STRING src, UNICODE_STRING dst, Uint16 len);
unsigned int UnicodeStrlen(UNICODE_STRING s);
