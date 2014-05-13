
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL_image.h>
#include "game.h"

using namespace std;

Game::Game (Vector2D displayDim, char *wndName, bool resizeable)
	: running (false), synchronized (false), powerSaving (false), curStage (0),
	framerateMeasured (0), framelenMeasured (0)
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
	setFramerate (50);
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
	if (synchronized) {
		runSynchronized ();
	}
	else {
		runPerformance ();
	}
}

void Game::runPerformance ()
{
	Uint64 lastFrameTick, nextFrameTick, lastUpdateTick, now;
	double timeDelta;
	
	lastFrameTick = nextFrameTick = lastUpdateTick = now = SDL_GetPerformanceCounter ();
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
		
		// Frame Drawing
		now = SDL_GetPerformanceCounter ();
		if (now >= nextFrameTick) {
		
			nextFrameTick += framelenTarget * perfFreq;
			framelenMeasured = (double)(now - lastFrameTick) / (double)perfFreq;
			framerateMeasured = 1 / framelenMeasured;
			lastFrameTick = now;
			
			display->clear ();
			display->activateScreenDrawMode ();
			drawMan->draw ();
			display->present ();
		}
	}
}

void Game::runSynchronized ()
{
	Uint64 nextFrameTick, lastFrameTick, now;
	int left;
	
	lastFrameTick = nextFrameTick = SDL_GetPerformanceCounter ();
	running = true;
	
	while (running) {
		
		now = SDL_GetPerformanceCounter ();
		if (now >= nextFrameTick) {

			nextFrameTick += framelenTarget * perfFreq;
			framelenMeasured = (double)(now - lastFrameTick) / (double)perfFreq;
			framerateMeasured = 1 / framelenMeasured;
			lastFrameTick = now;
			
			eventMan->update ();
			updateMan->update (framelenTarget);
			
			display->clear ();
			display->activateScreenDrawMode ();
			drawMan->draw ();
			display->present ();
		}
		
		if (powerSaving) {
			now = SDL_GetPerformanceCounter ();
			left = ((double)(nextFrameTick - SDL_GetPerformanceCounter ()) * 1000.0
				/ (double)perfFreq);
			if (left > 0) {
				SDL_Delay (left);
			}
		}
	}
}

void Game::setFramerate (double fps)
{
	framerateTarget = fps;
	framelenTarget = 1 / fps;
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

