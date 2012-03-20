#include "Main/Main.h"

#include <iostream>

Main::Main()
{
	Finished = false;
	pDisplay = NULL;
	pFont = NULL;

	TileWidth = TileHeight = 0;
	NumRows = NumCols = 0;

	GameMode = GM_NONE;
	InputMode = IM_NONE;

	PendingTicks = 0;

	//Testing Stuff
	PlayerEntity = -1;
	PuschelEntity = -1;
	ItemEntity = -1;
}

int Main::OnExecute()
{
	//Wenn die Initialisierung Fehlschlägt, kann das Programm nicht laufen
	if(!OnInit())
		return 0;//false

	char c;//Zwischenspeicherung eines Tastendrucks

	//Solange das Spiel nicht durch Benutzereingabe('q') oder Sieg/Vernichtung beendet wurde soll es weiterlaufen
	while(!Finished)
	{
		OnRender();//Anzeige des Spielbildschirms

		c = GetUserAction(&Event);
		HandleUserAction(c);
		while(PendingTicks)
			Tick();

	}

	//Zum Schluss werden Alle Ressourcen wieder Freigegeben, die möglicherweise verwendet wurden
	OnExit();

	return 1;//true
}

bool Main::OnInit()
{
	TileHeight = 32;
	TileWidth = TileHeight / 2;

	NumCols = 50;
	NumRows = 15;

	GameMode = GM_MAIN;
	InputMode = IM_MAIN;

	if(SDL_Init(SDL_INIT_EVERYTHING) > 0)
		return false;

	if(TTF_Init())
		return false;

	if((pDisplay = SDL_SetVideoMode(TileWidth * NumCols, TileHeight * NumRows,32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
		return false;

	SDL_WM_SetCaption("Abiturkomponente 5 - Roguelike", NULL);

	if((pFont = TTF_OpenFont("Font/video_terminal_screen_regular.ttf", TileHeight)) == NULL)
		return false;

	if(!sMain.OnInit(TileHeight, TileWidth, NumRows, NumCols))
		return false;

	if(!gMessages.OnInit(40))
		return false;

	if(!CItemTypeList::InitTypes())
		return false;

	if(!Map.InitWithGenerator(6,4,12,8))
		return false;

	Camera.Init(sMain.W()-16,sMain.H()-5);
	Camera.CenterCamera(CVector(0,0), Map.GetW(), Map.GetH());

	SDL_EnableUNICODE(1);

	//Testing Stuff

	PlayerEntity = Map.AddEntity(new CPlayer(Tile('@', CColor(255,0,255), CColor(0,0,0)), CVector(1,1), EF_MOB, 15, 25));

	Map.Recalculate_FOV(Map.GetEntity(PlayerEntity)->Pos);

	gMessages.AddMessage("Du erwachst in einem Dunklen Verlies");
	gMessages.AddMessage("Du weist nicht wie du hier hingekommen bist");
	gMessages.AddMessage("DU MUSST VON HIER ENTKOMMEN!");

	return true;
}

void Main::OnExit()
{
	Map.RemoveEntity(PlayerEntity);

	Map.OnExit();

	CItemTypeList::ExitTypes();

	gMessages.OnExit();

	sMain.OnExit();

	TTF_CloseFont(pFont);
	SDL_FreeSurface(pDisplay);

	TTF_Quit();
	SDL_Quit();
}

void Main::OnRender()
{
	SDL_FillRect(pDisplay, NULL, SDL_MapRGB(pDisplay->format, 0,0,0));

	sMain.ClearScreen();

	switch(GameMode)
	{
	case GM_MAIN:
	case GM_DEAD:
	case GM_EXIT:
		if(!gMessages.PrintMessages(&sMain, 0, 0, 5,  false))
			gMessages.AddMessage("PrintMessages schlug fehl");

		Map.DrawMap(&sMain, 0, 5, Camera.GetX(), Camera.GetY(), Camera.GetW(), Camera.GetH());

		sMain.PutFText(CL_WHITE, CL_BLACK, sMain.W() - 16, 5, 16, "HP: %d(%d)", Map.GetEntity(PlayerEntity)->GetHealth(), Map.GetEntity(PlayerEntity)->GetMaxHealth());
		sMain.PutFText(CL_WHITE, CL_BLACK, sMain.W() - 16, 6, 32, "Item:\n%s", Map.GetEntity(PlayerEntity)->WieldsItem() ? ((CPlayer*)Map.GetEntity(PlayerEntity))->WieldedItem->GetName() : "Nichts");

		if(GameMode == GM_DEAD) {
			sMain.PutText("Du bist Tot", CColor(220,20,20), CL_BLACK, sMain.W() / 2 - 5, sMain.H() / 2);//strlen("du ...") / 2 -> 5
			sMain.PutText("Druecke Enter um neu zu beginnen", CColor(220, 200, 200), CL_BLACK, sMain.W() / 2 - 16, sMain.H() / 2 + 1);
		} else if(GameMode == GM_EXIT) {
			sMain.PutText("Du bist entkommen!", CColor(20,20,200), CL_BLACK, sMain.W() / 2 - 9, sMain.H() / 2);
			sMain.PutText("Herzlichen Glueckwunsch", CL_WHITE, CL_BLACK, sMain.W() / 2 - 11, sMain.H() / 2 + 1);
		}
		break;

	case GM_MESSAGE_ARCHIVE:
		if(!gMessages.PrintMessages(&sMain, 0, 0, NumRows, true))
			gMessages.AddMessage("PrintMessages schlug fehl");
		break;

	/*case GM_CRAFTING:
		Crafting.Render(&sMain);
		break;*/

	default:
		break;
	}

	sMain.Render(pDisplay, pFont);

	SDL_Flip(pDisplay);
}

void Main::Tick()
{
	gMessages.Tick();
	Map.Tick();

	Camera.CenterCamera(Map.GetEntity(PlayerEntity)->Pos, Map.GetW(), Map.GetH());

	if(!Map.GetEntity(PlayerEntity)->IsAlive(&Map)) {
		gMessages.AddMessage("Du stirbst");
		GameMode = GM_DEAD;
	} else if(Map.GetTile(Map.GetEntity(PlayerEntity)->Pos) == CMapTile::ExitTile) {
		gMessages.AddMessage("Du hast es geschaft den Verliesen zu entkommen");
		GameMode = GM_EXIT;
	}

	PendingTicks--;
}

/**
 * @function: Stellt die Frage mit dem Text
 *  @param QuestionText
 *
 * Gibt Ja zurück, wenn die Taste 'y' gedrückt wurde oder Nein bei 'n' oder wenn ein Fehler auftrat
 **/
bool Main::Question(const char* QuestionText)
{
	char c;
	do {
		gMessages.AddMessage(QuestionText);
		OnRender();//Flush Screen

		c = GetUserAction(&Event);

		if(!c)//Fenster Geschlossen
			return false;

		if(c == 'n' || c == 'q')
			return false;
		else if(c == 'y')
			return true;
		else { //Fehlerhafte Eingabe
			gMessages.AddMessage("Bitter entweder (y)es oder (n)o eingeben");
		}

	} while(true);

	return false;//should never happen
}

int main(int argc, char** argv)
{
	Init_Random();

	Main App;
	return App.OnExecute();
}
