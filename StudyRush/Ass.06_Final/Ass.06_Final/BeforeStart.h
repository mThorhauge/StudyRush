#pragma once
//////////////////////////////////////// ALLEGRO AND COMMON LIBRARIES
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h" //// IMAGE LOADING
#include "stdio.h"

/////////////////////////////////////// MY LIBRARIES
#include"GameType.h"

class BeforeStart{

public:

	//// KEYBOARD
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_MOUSE_STATE mouse_state;

	//// ONE PLAYER OR TWO PLAYER
	GAMETYPE gametype;

	//// EVENTS
	ALLEGRO_EVENT_QUEUE * event_queue;

	//// SCREENS
	ALLEGRO_BITMAP * screen;
	ALLEGRO_BITMAP * title;
	ALLEGRO_BITMAP * name;
	ALLEGRO_BITMAP * control;
	ALLEGRO_BITMAP * story;
	ALLEGRO_BITMAP * select;

	bool start;
	bool _title;
	bool _control;
	bool _story;
	bool _select;

	BeforeStart();
	~BeforeStart();

	void Run();
	void TitleScreen();
	void SelectScreen();
	void ControlsScreen();
	void StoryScreen();
	void Start();
	
};

