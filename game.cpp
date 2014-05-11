
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL_image.h>
#include "game.h"

using namespace std;

Game::Game (Vector2D displayDim, char *wndName, bool resizeable)
	: running (false), powerSaving (false), curStage (0)
{
	if (SDL_Init (SDL_INIT_VIDEO) != 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}
	
	if (IMG_Init (IMG_INIT_PNG) == 0) {
		cerr << "IMG error: " << IMG_GetError () << endl;
		exit (-1);
	}
	
	if (FT_Init_FreeType (&freeType)) {
		cerr << "FreeType error" << endl;
		exit (-1);
	}
	
	eventMan = new EventManager ();
	display = new Display (this, displayDim, wndName, resizeable);
	drawMan = new DrawManager ();
	updateMan = new UpdateManager ();
	texMan = new TextureManager (this, "res");
	
	eventMan->registerHandler (SDL_QUIT, this);
	
	srand (time(0));
	perfFreq = SDL_GetPerformanceFrequency ();
	setFramerate (60);
}

Game::~Game ()
{
	eventMan->unregisterHandler (SDL_QUIT, this);
	
	delete texMan;
	delete updateMan;
	delete drawMan;
	delete display;
	delete eventMan;
	
	FT_Done_FreeType (freeType);
	IMG_Quit ();
	SDL_Quit ();
}

void Game::run ()
{
	if (powerSaving) {
	}
	else {
		runPerformance ();
	}
}

void Game::runPerformance ()
{
	Uint64 lastFrameTick, lastUpdateTick, now;
	double timeDelta;
	
	lastFrameTick = lastUpdateTick = now = SDL_GetPerformanceCounter ();
	running = true;
	
	while (running) {
	
		// Calculate Time Difference
		now = SDL_GetPerformanceCounter ();
		timeDelta = (double)(now - lastUpdateTick) / (double)perfFreq;
		lastUpdateTick = now;
	
		// Event Handling
		eventMan->update ();
		
		// Updating
		updateMan->update (timeDelta);
		/*
		if (curStage) {
			// Update Stage
			curStage->update (timeDelta);
			// Update Sprites
			spriteMan->update (timeDelta);
		}
		*/
		
		// Frame Drawing
		now = SDL_GetPerformanceCounter ();
		if (now - lastFrameTick > framelenTarget * perfFreq) {
			framelenMeasured = (double)(now - lastFrameTick) / (double)perfFreq;
			framerateMeasured = 1 / framelenMeasured;
			lastFrameTick = now;
			display->clear ();
			display->activateScreenDrawMode ();
			/*
			if (curStage) {
				curStage->drawBg ();
				spriteMan->draw ();
				curStage->drawFg ();
			}
			*/
			drawMan->draw ();
			display->present ();
		}
	}
}

void Game::setFramerate (double f)
{
	framerateTarget = f;
	framelenTarget = 1 / f;
}

void Game::enterStage (Stage *stage)
{
	curStage = stage;
	curStage->enter ();
}

void Game::leaveStage ()
{
	if (curStage) {
		curStage->leave ();
		curStage = 0;
	}
}

void Game::changeStage (Stage *stage)
{
	leaveStage ();
	enterStage (stage);
}

void Game::onQuit (SDL_QuitEvent)
{
	running = false;
}

