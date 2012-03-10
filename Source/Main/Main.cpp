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

	if(!sMap.OnInit(TileHeight, TileWidth, 6, 6))
		return false;

	if(!gMessages.OnInit(40))
		return false;

	if(!Map.OnInit(6,6))
		return false;

	SDL_EnableUNICODE(1);

	//Testing Stuff
	Map.ClearMap(CMapTile::WallTile);
	for(Uint32 Y=1;Y<(Map.GetH()-1);Y++)
		for(Uint32 X=1;X<(Map.GetW()-1);X++)
			Map.GetTile(CVector(X, Y)) = CMapTile::GroundTile;

	Map.GetTile(CVector(2,1)) = CMapTile::DoorTile;
	Map.GetTile(CVector(2,2)) = CMapTile::WallTile;
	Map.GetTile(CVector(2,3)) = CMapTile::DoorTile;
	Map.GetTile(CVector(2,4)) = CMapTile::WallTile;
	Map.GetTile(CVector(3,2)) = CMapTile::WallTile;
	Map.GetTile(CVector(4,2)) = CMapTile::WallTile;

	Map.GetTile(CVector(4,4)) = CMapTile::FarmTile;
	Map.GetTileData(CVector(4,4)).Clear();
	Map.GetTileData(CVector(4,4)).Set(0 | FTD_NO_PLANT);


	PlayerEntity = Map.AddEntity(new CMobEntity(Tile('@', CColor(255,0,255), CColor(0,0,0)), CVector(1,1), EF_MOB | EF_PLAYER));

	PuschelEntity =	Map.AddEntity(new CMobEntity(Tile('&', CColor(255,0,0), CColor(0,0,0)), CVector(3,1), EF_MOB));

	CItem* pItem = new CItem(IT_SEED, SIED_PLUMPHELMET, 1);
	ItemEntity = Map.AddEntity(new CItemEntity(pItem, CVector(1,2)));
	delete pItem;

	return true;
}

void Main::OnExit()
{
	Map.RemoveEntity(ItemEntity);
	Map.RemoveEntity(PuschelEntity);
	//pPuschel = NULL;
	Map.RemoveEntity(PlayerEntity);
	//pPlayer = NULL;

	Map.OnExit();
	gMessages.OnExit();

	sMap.OnExit();
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
		if(!gMessages.PrintMessages(&sMain, 0, 0, 5,  false))
			gMessages.AddMessage("PrintMessages schlug fehl");

		Map.DrawMap(&sMap, 0,0);
		sMain.PutScreen(&sMap, 2, 6);
		break;
	case GM_MESSAGE_ARCHIVE:
		if(!gMessages.PrintMessages(&sMain, 0, 0, NumRows, true))
			gMessages.AddMessage("PrintMessages schlug fehl");
		break;
	case GM_CRAFTING:
		Crafting.Render(&sMain);
		break;
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
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	Init_Random();

	std::cout << "HOHOHOHO!" << std::endl;

	Main App;
	return App.OnExecute();
}
