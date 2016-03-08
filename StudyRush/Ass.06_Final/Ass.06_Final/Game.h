/////////////////////////////////////// ALLEGRO LIBRARIES
#pragma once
#include <allegro5/allegro_ttf.h>   
#include <allegro5/allegro_font.h>  

#include <allegro5/allegro_audio.h>	 //// AUDIO
#include <allegro5/allegro_acodec.h> //// CODEC AUDIO

////////////////////////////////////// MY LIBRARIES
#include "Sprites.h"
#include "Player.h"
#include "Librarians.h"
#include "Render.h"
#include "Physics.h"
#include "Audio.h"

class Game {

public:

	//// GAME OBJECTS
	Sprites book[NUM_BOOKS];
	Sprites StaticBookcase;
	Player player;
	Player playerTwo;
	Librarians librarian[NUM_ENEMIES];

	//// IMPORTENT CLASSES
	Render render;
	Physics physics;
	Audio audio;

	//// GAME SCREENS
	ALLEGRO_BITMAP * background;
	ALLEGRO_BITMAP * endScreen;
	ALLEGRO_BITMAP * SplitScreen;
	ALLEGRO_BITMAP * screen[2];

	//// TIMERS AND EVENTS
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER * timer;
	ALLEGRO_TIMER * frameRate;
	ALLEGRO_TIMER * timeLeft;
	ALLEGRO_TIMER * respawn[2];				//// RESPAWN | 0 -> PLAYER ONE | 1 -> PLAYER TWO

	//// END GAME
	bool quit;
	bool end;

	Game();
	~Game();

	void Init();
	void PlaceBooks();                       //// SET X, Y, AND BITMAP
	void PlaceLibrarians();                  //// SET X, Y, DIRECTION AND BITMAPS
	void SwapBooks(int booknum);             //// ONE BOOK DISAPPEARS, ANOTHER APPEARS
	//void Update();							 //// GAME CYCLE
	void PlayerControls();					 //// KEY INPUTS
	void PlayerTwoControls();				 //// KEY INPUTS
	//void Draw(ALLEGRO_DISPLAY * display);	 //// DRAW THINGS
	//void Run(ALLEGRO_DISPLAY * display);	 //// RUN GAME
	void End();								 //// GAME OVER
	void Destroy();							 //// STOP TIMERS (DESTROY MOVED TO ~GAME())
};
