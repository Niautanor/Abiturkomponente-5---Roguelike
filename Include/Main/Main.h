/**
 * @file The Main class for the Application
 *
 * Dies ist die Klasse, die von der Anwendung instanziert wird.
 * sie übernimmt von da an alle weiteren Aufgaben von der Ausgabe des Bildschirms bis zur Abfrage von Benutzereingaben
 */

#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "HelperAPI/Random.h"

#include "HelperAPI/CNameable.h"

#include "HelperAPI/NameableList.h"

#include "Main/Screen.h"

//#include "Main/CraftingInterface.h"

#include "Map/Map.h"
#include "Map/Camera.h"
#include "CMessageQueue.h"

enum eGameMode
{
	GM_NONE = 0,
	GM_MAIN,
	GM_MESSAGE_ARCHIVE,
	GM_DEAD,
	GM_EXIT,
	//GM_CRAFTING
};

enum eInputMode
{
	IM_NONE = 0,
	IM_MAIN,
	IM_INTERACT,
	IM_EXAMINE,
	IM_USE
};

class Main
{
private:
	bool Finished;//Diese Variable gibt an, ob das Spiel noch läuft(true) oder nicht(false)

	SDL_Surface* pDisplay;//Das Objekt, dass alle Daten zum Tatsächlichen Spielfenster enthält
	TTF_Font* pFont;//Die Schriftart, die Verwendet wird um den Bildschirm anzuzeigen

	SDL_Event Event;//Das SDL_Event, dass zum Empfangen von Tastendrücken u.ä verwendet wird

	Uint16 TileWidth, TileHeight;//Asdf
	Uint16 NumRows, NumCols;

	Screen sMain;

	eGameMode GameMode;
	eInputMode InputMode;

	CCamera Camera;

	CMap Map;

	//CraftingInterface Crafting;

	Uint16 PendingTicks;//Die Anzahl der Spielschritte die ausgeführt werden muss bevor der Spieler wieder eine Entscheidung treffen kann

	int PlayerEntity;
	int PuschelEntity;
	int ItemEntity;

public:
	Main();

	//Diese Funktion wird von beim Start der Anwendung aufgerufen und ihr wert zurückgegeben
	int OnExecute();

	//Diese Funktion Initialisiert das Spiel(Alle benötigten Daten werden geladen und auf ihre Integrität geprüft)
	bool OnInit();

	//Der Aufräumprozess gibt alle Belegten Speicherbereiche wieder Frei und kümmert sich unter Umständen auch um das Speichern von Statusinformationen
	void OnExit();

	//Mithilfe dieser Prozedur wird die Welt auf dem Bildschirm angezeigt -> FlushScreen
	void OnRender();

	//Kümmert sich um alle Benutzeraktionen und beendet gegebenenfals das Spiel
	Uint16 GetUserAction(SDL_Event* pEvent);

	//Stellt dem Spieler eine Frage, die er mit Ja oder nein beantworten kann
	bool Question(const char* QuestionText);

	template<class P>Uint8 ListQuestion(const char* QuestionText, PtrList<P> List);//IMPORTANT: The Template Argument should be a derived from CNameable*

	//Bewegt das Spiel
	void Tick();

	//Reagiert auf den Druck der Taste C
	void HandleUserAction(Uint16 c);

	//Reagiert auf den Druck einer Richtungstaste(1,2,3,4,6,7,8,9)
	void HandleDirectionKey(CVector Dir);
};

template<class P>Uint8 Main::ListQuestion(const char* QuestionText, PtrList<P> List)
{
	if(List.empty())
		return 0;

	gMessages.AddMessage(QuestionText);
	for(Uint16 i=0;i<List.size();i++){
		gMessages.AddFMessage(" %c - %s", 'a' + i, List[i]->GetName());
	}

	char c;
	do {
		OnRender();

		c = GetUserAction(&Event);

		if(c < 'a' || c > 'z') {
			gMessages.AddMessage("kleinbuchstabe von a bis z eingeben");
			continue;
		} else {
			if((Uint8)(c-'a') < List.size())
				return c - 'a';
			else {
				gMessages.AddMessage("du kannst nur Elemente aus der Liste auswählen");
				continue;
			}
		}
	} while(c != '\0');

	return 0;
}
