/**
 * @file The Main class for the Application
 *
 * Dies ist die Klasse, die von der Anwendung instanziert wird.
 * sie �bernimmt von da an alle weiteren Aufgaben von der Ausgabe des Bildschirms bis zur Abfrage von Benutzereingaben
 */

#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Main/Screen.h"

#include "Map/CMap.h"
#include "CMessageQueue.h"

class Main
{
private:
	bool Finished;//Diese Variable gibt an, ob das Spiel noch l�uft(true) oder nicht(false)

	SDL_Surface* pDisplay;//Das Objekt, dass alle Daten zum Tats�chlichen Spielfenster enth�lt
	TTF_Font* pFont;//Die Schriftart, die Verwendet wird um den Bildschirm anzuzeigen

	Uint16 TileWidth, TileHeight;
	Uint16 NumRows, NumCols;

	Screen sMain;
	Screen sMap;

	CMessageQueue Messages;
	CMap Map;

	Uint16 AtX, AtY;

public:
	Main();

	//Diese Funktion wird von beim Start der Anwendung aufgerufen und ihr wert zur�ckgegeben
	int OnExecute();

	//Diese Funktion Initialisiert das Spiel(Alle ben�tigten Daten werden geladen und auf ihre Integrit�t gepr�ft)
	bool OnInit();

	//Der Aufr�umprozess gibt alle Belegten Speicherbereiche wieder Frei und k�mmert sich unter Umst�nden auch um das Speichern von Statusinformationen
	void OnExit();

	//Mithilfe dieser Prozedur wird die Welt auf dem Bildschirm angezeigt
	void OnRender();

	//K�mmert sich um alle Benutzeraktionen und beendet gegebenenfals das Spiel
	Uint16 GetUserAction(SDL_Event* pEvent);

	//Reagiert auf den Druck der Taste C
	void HandleUserAction(Uint16 c);
};
