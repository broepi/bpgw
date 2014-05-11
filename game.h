
#ifndef GAME_H
#define GAME_H

#include <set>
#include <SDL2/SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "eventmanager.h"
#include "drawmanager.h"
#include "updatemanager.h"
#include "texturemanager.h"
#include "display.h"
#include "stage.h"
#include "vector2d.h"

using namespace std;

class Game : public EventHandler
{
public:
	bool running;
	bool powerSaving;
	Uint64 perfFreq;
	double framerateTarget; // frames per second
	double framelenTarget; // seconds per frame
	double framerateMeasured; // frames per second
	double framelenMeasured; // seconds per frame
	FT_Library freeType;
	EventManager *eventMan;
	Display *display;
	DrawManager *drawMan;
	UpdateManager *updateMan;
	TextureManager *texMan;
	Stage *curStage;
	
	Game (Vector2D displayDim = Vector2D (800, 600), char *wndName = "My Game",
		bool resizeable = false);
	~Game ();
	void run ();
	void runPerformance ();
	void setFramerate (double f);
	void enterStage (Stage *stage);
	void leaveStage ();
	void changeStage (Stage *stage);
	
	void onQuit (SDL_QuitEvent event);
};

#endif

