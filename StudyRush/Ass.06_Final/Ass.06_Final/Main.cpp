////////////////////////////////////////////// ALLEGRO AND COMMON LIBRARIES
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"  //// IMAGE LOADING
#include <allegro5/allegro_ttf.h>    //// TTF FONTS
#include <allegro5/allegro_font.h>   //// FONTS
#include <allegro5/allegro_audio.h>	 //// AUDIO
#include <allegro5/allegro_acodec.h> //// CODEC AUDIO
#include "stdio.h"

///////////////////////////////////////// MY LIBRARIES
#include "Sprites.h"
#include "DefinedValues.h"
#include "Game.h"
#include "OneP.h"
#include "TwoP.h"
#include "Render.h"
#include "BeforeStart.h"
#include "GameType.h"

ALLEGRO_DISPLAY* display = NULL;

void InitAllegro(int W, int H){

	fprintf(stderr, "start!\n");

	//// INITIALIZE ALLEGRO
	if (!al_init()){
		fprintf(stderr, "failed to initialize allegro!\n");
	}

	//// INITIALIZE IMAGE ADDON
	if (!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image addon!\n");
	}

	//// INITIALIZE GAME DISPLAY
	ALLEGRO_BITMAP * icon;
	icon = al_load_bitmap("bitmaps/icon.png");

	display = al_create_display(W, H);
	al_set_window_title(display, "Assignment 06 ~~ Library Game ~~");
	al_set_display_icon(display, icon);

	if (!display){
		fprintf(stderr, "failed to create display!\n");
		exit(0);
	}

	//// INITIALIZE KEYBOARD
	if (!al_install_keyboard()){
		fprintf(stderr, "failed to install keyboard!\n");
		exit(0);
	}

	////INITIALIZE MOUSE
	if (!al_install_mouse()){
		fprintf(stderr, "failed to install mouse!\n");
		exit(0);
	}

	//// INITIALIZE FONTS
	al_init_font_addon();
	al_init_ttf_addon();

	////INITIALIZE SOUND
	if(!al_install_audio())
		fprintf(stderr, "failed to install audio!\n");
	al_init_acodec_addon();
};

void endAllegro(){	//// DESTROY DISPLAY
	al_destroy_display(display);
};

void main(){ //// MAIN GAME FUNCTION

	InitAllegro(SCREEN_WIDTH, SCREEN_HEIGHT); //// INITIALIZE ALLEGRO

	BeforeStart menue;
	al_register_event_source(menue.event_queue, al_get_display_event_source(display)); //// LOOK FOR WINDOW EVENTS
	menue.Run();


	/////////////// ONE PLAYER GAME////////////////////
	if (menue.gametype == ONEPLAYER){ 
		
		OneP game; //// CREATE GAME
		al_register_event_source(game.event_queue, al_get_display_event_source(display)); //// LOOK FOR WINDOW EVENTS
		game.Run(); //// RUN GAME
	}

	/////////////// TWO PLAYER GAME////////////////////
	if (menue.gametype == TWOPLAYER){
		TwoP game; //// CREATE GAME
		al_register_event_source(game.event_queue, al_get_display_event_source(display)); //// LOOK FOR WINDOW EVENTS
		game.Run(display); //// RUN GAME
	}

	endAllegro(); //// DESTROY DISPLAY
};