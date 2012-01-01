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

	PendingTicks = 0;

	//Testing Stuff
	pPlayer = NULL;
}

int Main::OnExecute()
{
	//Wenn die Initialisierung Fehlschlägt, kann das Programm nicht laufen
	if(!OnInit())
		return 0;//false

	SDL_Event Event;

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

	if(!sMap.OnInit(TileHeight, TileWidth, 5, 5))
		return false;

	if(!Messages.OnInit(40))
		return false;

	if(!Map.OnInit(5,5))
		return false;

	SDL_EnableUNICODE(1);

	//Testing Stuff
	Map.ClearMap(CMapTile::WallTile);
	for(Uint32 Y=1;Y<(Map.GetH()-1);Y++)
		for(Uint32 X=1;X<(Map.GetW()-1);X++)
			Map.GetTile(CVector(X, Y)) = CMapTile::GroundTile;

	pPlayer = new CEntity;
	Map.AddEntity(pPlayer);

	return true;
}

void Main::OnExit()
{
	Map.RemoveEntity(pPlayer);
	//pPlayer = NULL;
	Map.OnExit();
	Messages.OnExit();

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
		if(!Messages.PrintMessages(&sMain, 0, 0, 5,  false))
			Messages.AddMessage("PrintMessages schlug fehl");

		Map.DrawMap(&sMap, 0,0);
		sMain.PutScreen(&sMap, 2, 6);
		break;
	case GM_MESSAGE_ARCHIVE:
		if(!Messages.PrintMessages(&sMain, 0, 0, NumRows, true))
			Messages.AddMessage("PrintMessages schlug fehl");
		break;
	default:
		break;
	}

	sMain.Render(pDisplay, pFont);

	SDL_Flip(pDisplay);
}

void Main::Tick()
{
	Messages.Tick();
	Map.Tick();
	PendingTicks--;
}

int main(int argc, char** argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	std::cout << "HOHOHOHO!" << std::endl;

	Main App;
	return App.OnExecute();
}


