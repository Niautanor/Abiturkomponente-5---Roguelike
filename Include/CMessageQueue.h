/*
 * CMessageQueue.h
 *
 *  Created on: 16.09.2011
 *      Author: Tim
 */

#pragma once /*CMESSAGEQUEUE_H_*/

#include <SDL/SDL.h>

#include "Unicode.h"

#include "Screen.h"

class CMessageQueue
{
private:
	Uint16 StartX, StartY;//Anfangskoordinaten der Zu Rendernden Nachrichten
	Uint16 MaxMessages;//MaximaleAnzahl nachrichten
	Uint16 NumMessages;

	UNICODE_STRING* Messages;//Undefiniert langes Array für nachrichten ( wird bei Init() Messages[MaxMessages])

public:
	CMessageQueue();//Standardkonstruktor

	bool OnInit(Uint16 X, Uint16 Y, Uint16 Max);
	void OnExit();

	//Löscht alle Nachrichten und entfernt sie vom Bildschirm
	void Clear();

	//Zeigt alle Nachrichten auf dem Bildschirm an
	bool PrintMessages(Screen* s);

	//Fügt die Angegeben Nachricht dem Nachrichtenpuffer hinzu
	void AddMessage(UNICODE_STRING M);
	void AddMessage(const char* M);
};
