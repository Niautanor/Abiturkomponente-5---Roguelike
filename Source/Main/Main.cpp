#include "Main/Main.h"

Main::Main()
{
	Finished = false;
	pDisplay = NULL;
	pFont = NULL;

	TileWidth = TileHeight = 0;
	NumRows = NumCols = 0;

	AtX = AtY = 0;
}

int Main::OnExecute()
{
	//Wenn die Initialisierung Fehlschlägt, kann das Programm nicht laufen
	if(!OnInit())
		return 0;//false

	SDL_Event Event;

	Uint16 c;//Zwischenspeicherung eines Tastendrucks

	//Solange das Spiel nicht durch Benutzereingabe('q') oder Sieg/Vernichtung beendet wurde soll es weiterlaufen
	while(!Finished)
	{
		OnRender();//Anzeige des Spielbildschirms

		c = GetUserAction(&Event);
		HandleUserAction(c);

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

	if(!sMap.OnInit(TileHeight, TileWidth, 5, 4))
		return false;

	if(!Messages.OnInit(0,0,5))
		return false;

	if(!Map.OnInit(4,5))
		return false;

	Map.ClearMap(CMapTile(Tile('#',CColor(0,255,0),CColor(0,0,0)), MTF_EXISTANT | MTF_VISIBLE));
	Map.GetTile(1, 2)->Flags.Unset(MTF_VISIBLE);

	SDL_EnableUNICODE(1);

	return true;
}

void Main::OnExit()
{
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
	sMain.Put(Tile('@', CColor(255,0,0), CColor(0,0,0)),AtX,AtY);

	if(!Messages.PrintMessages(&sMain))
		Messages.AddMessage("PrintMessages schlug fehl");

	char Text[] = "ASDF! .. ####";
	sMain.PutText(Text, CColor(255,255,255),CColor(0,0,0), 1,5);

	Map.DrawMap(&sMap, 0,0);
	sMain.PutScreen(&sMap, 2, 6);

	sMain.Render(pDisplay, pFont);

	SDL_Flip(pDisplay);
}

int main(int argc, char** argv)
{
	Main App;
	return App.OnExecute();
}


