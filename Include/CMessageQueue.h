/*
 * CMessageQueue.h
 *
 *  Created on: 16.09.2011
 *      Author: Tim
 */

#pragma once /*CMESSAGEQUEUE_H_*/

#include <SDL/SDL.h>

#include "HelperAPI/PtrList.h"

#include "Main/Screen.h"

struct SMessage
{
	char* Text;
	Uint16 Lifetime;
	bool Visible;
};

class CMessageQueue
{
private:
	Uint16 MaxMessages;//MaximaleAnzahl nachrichten
	Uint16 NumMessages;
	Uint16 MessageLifetime;

	SMessage* Messages;//Undefiniert langes Array für nachrichten ( wird bei Init() Messages[MaxMessages])

public:
	CMessageQueue();//Standardkonstruktor

	bool OnInit(Uint16 Max, Uint16 MessageLifetime = 5);
	void OnExit();

	//Löscht alle Nachrichten und entfernt sie vom Bildschirm
	void Clear();

	//Zeigt alle Nachrichten auf dem Bildschirm an | ArchiveMode -> Alle Nachrichten Anzeigen
	bool PrintMessages(Screen* s, Uint16 StartX, Uint16 StartY, Uint16 MaxMessagesOnScreen, bool ArchiveMode = false);

	//Fügt die Angegeben Nachricht dem Nachrichtenpuffer hinzu
	void AddMessage(const char* M);

	//Setzt eine Nachricht mit sprintf zusammen und fügt sie der Nachrichtenkette hinzu
	void AddFMessage(const char* Format, ...);

	//Prüft ob Nachrichten zu alt geworden sind um noch dargestellt zu werden
	void Tick();
};

extern CMessageQueue gMessages;
