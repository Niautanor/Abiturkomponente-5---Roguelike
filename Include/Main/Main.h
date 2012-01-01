/**
 * @file The Main class for the Application
 *
 * Dies ist die Klasse, die von der Anwendung instanziert wird.
 * sie übernimmt von da an alle weiteren Aufgaben von der Ausgabe des Bildschirms bis zur Abfrage von Benutzereingaben
 */

#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Main/Screen.h"

#include "Map/Map.h"
#include "CMessageQueue.h"

enum eGameMode
{
	GM_NONE = 0,
	GM_MAIN,
	GM_MESSAGE_ARCHIVE
};

class Main
{
private:
	bool Finished;//Diese Variable gibt an, ob das Spiel noch läuft(true) oder nicht(false)

	SDL_Surface* pDisplay;//Das Objekt, dass alle Daten zum Tatsächlichen Spielfenster enthält
	TTF_Font* pFont;//Die Schriftart, die Verwendet wird um den Bildschirm anzuzeigen

	Uint16 TileWidth, TileHeight;//Asdf
	Uint16 NumRows, NumCols;

	Screen sMain;
	Screen sMap;

	eGameMode GameMode;

	CMessageQueue Messages;
	CMap Map;

	Uint16 PendingTicks;//Die Anzahl der Spielschritte die ausgeführt werden muss bevor der Spieler wieder eine Entscheidung treffen kann

	CEntity* pPlayer;

public:
	Main();

	//Diese Funktion wird von beim Start der Anwendung aufgerufen und ihr wert zurückgegeben
	int OnExecute();

	//Diese Funktion Initialisiert das Spiel(Alle benötigten Daten werden geladen und auf ihre Integrität geprüft)
	bool OnInit();

	//Der Aufräumprozess gibt alle Belegten Speicherbereiche wieder Frei und kümmert sich unter Umständen auch um das Speichern von Statusinformationen
	void OnExit();

	//Mithilfe dieser Prozedur wird die Welt auf dem Bildschirm angezeigt
	void OnRender();

	//Kümmert sich um alle Benutzeraktionen und beendet gegebenenfals das Spiel
	Uint16 GetUserAction(SDL_Event* pEvent);

	//Bewegt das Spiel
	void Tick();

	//Reagiert auf den Druck der Taste C
	void HandleUserAction(Uint16 c);
};
