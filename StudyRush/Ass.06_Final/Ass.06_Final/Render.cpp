///////////////////////// ALLEGRO AND COMMON LIBRARIES
#include <stdio.h>
#include "allegro5/allegro.h"
//use image addon for loading images
#include <allegro5/allegro_image.h>

///////////////////////// MY LIBRARIES
#include "DefinedValues.h"
#include "Sprites.h"
#include "Player.h"
#include "Render.h"

Render::Render(){
	Init(); //// INITIALIZE CAMERAS

	////SET FONTS
	wonderland = al_load_font("Fonts/beyond_wonderland/beyond_wonderland.ttf", 24, NULL);
};

Render::~Render(){////DESTROY/ DEALLOCATE MEMORY
	al_destroy_font(wonderland);
};

void Render::Init(){ //// INITIALIZE CAMERAS

	cameraPosition[0] = 10;
	cameraPosition[1] = 10;

	cameraTwoPosition[0] = 10;
	cameraTwoPosition[1] = 10;
};

void Render::Start(ALLEGRO_BITMAP* bg){
	al_draw_bitmap(bg, 0, 0, 0);
};

void Render::Draw(Sprites* a){ // DRAW THINGS (1 CELL X 1 CELL)

	float alpha = a->visible / 100.0f;
	al_convert_mask_to_alpha(a->sprite, al_map_rgb(255, 0, 255));

	/*
	al_draw_tinted_bitmap_region(
		source,
		tinted colour (alpha channel for this)
		start point x
		start point y
		width of region
		height of region
		x
		y
		flags (ALLEGRO_FLIP_HORIZONTAL or ALLEGRO_FLIP_VERTICAL)
	)
	*/

	//// DRAW SPECIFIED AREA OF FULL IMAGE
	al_draw_tinted_bitmap_region(a->sprite, al_map_rgba_f(1 * alpha, 1 * alpha, 1 * alpha, alpha),
		SPRITECELL*a->cellColoumb, SPRITECELL*a->cellRow, SPRITECELL, SPRITECELL, a->x,a-> y, 0);
};

void Render::DrawObsticals(Sprites* a){ // DRAW THINGS (1 CELL X 2 CELLS)

	float alpha = a->visible / 100.0f;
	al_convert_mask_to_alpha(a->sprite, al_map_rgb(255, 0, 255));

	///// DRAW SPECIFIED AREA OF FULL IMAGE
	al_draw_tinted_bitmap_region(a->sprite, al_map_rgba_f(1 * alpha, 1 * alpha, 1 * alpha, alpha),
		SPRITECELL*a->cellColoumb, 0, SPRITECELL, SPRITECELL*2, a->x, a->y, 0);
};

void Render::DrawScreens(ALLEGRO_BITMAP * screen, ALLEGRO_BITMAP * screen2, ALLEGRO_BITMAP * split){ //// DRAW SPLIT SCREENS

	al_draw_bitmap(screen, 0, 0, NULL);
	al_draw_bitmap(screen2, SCREEN_WIDTH / 2, 0, NULL);
	al_draw_bitmap(split, 0, 0, NULL);
};

void Render::DrawMessage(ALLEGRO_BITMAP * screen){ //// DRAW GAME MESSAGES

	al_draw_bitmap(screen, 0, 0, NULL);
};

void Render::End(){ ////FLIP DISPLAY
	al_flip_display();
};



////////////// FOR ONE PLAYER GAMES/////////////////
void Render::CameraUpdateTwo(Player * a) {

	//////////////////////// CAMERA ONE ////////////////////////////////////////////////
	cameraPosition[0] = -(SCREEN_WIDTH / 2) + (a->x + SPRITECELL / 2);
	cameraPosition[1] = -(SCREEN_HEIGHT / 2) + (a->y + SPRITECELL / 2);

	//// CAMERA MOVEMENT LIMITS
	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;

	if (cameraPosition[0] > MAP_WIDTH - SCREEN_WIDTH / 2)
		cameraPosition[0] = MAP_WIDTH - SCREEN_WIDTH / 2;
	if (cameraPosition[1] > MAP_HEIGHT - SCREEN_HEIGHT)
		cameraPosition[1] = MAP_HEIGHT - SCREEN_HEIGHT;
};

void Render::CameraTransformTwo(){

	///////////////////// CAMERA ONE ///////////////////////
	al_identity_transform(&camera);
	al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
	al_use_transform(&camera);
};

void Render::DrawWordsTwo(int i, int sec){ //// DRAW TEXT

	//// PLAYER ONE
	al_draw_text(wonderland, al_map_rgb(0, 0, 0), cameraPosition[0], cameraPosition[1] + 25, ALLEGRO_ALIGN_LEFT, "Score: ");
	al_draw_textf(wonderland, al_map_rgb(0, 0, 0), cameraPosition[0] + 60, cameraPosition[1] + 25, ALLEGRO_ALIGN_LEFT, "%d", i);

	//// TIME LEFT
	al_draw_textf(wonderland, al_map_rgb(0, 0, 0), cameraPosition[0] + 50, cameraPosition[1], ALLEGRO_ALIGN_CENTER, "%d", sec);
};

////////////// FOR TWO PLAYER GAMES/////////////////
void Render::CameraUpdate(Player * a, Player * b) {

	//////////////////////// CAMERA ONE ////////////////////////////////////////////////
	cameraPosition[0] = -(SCREEN_WIDTH / 2 / 2) + (a->x + SPRITECELL / 2);
	cameraPosition[1] = -(SCREEN_HEIGHT / 2) + (a->y + SPRITECELL / 2);

	//// CAMERA MOVEMENT LIMITS
	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;

	if (cameraPosition[0] > MAP_WIDTH - SCREEN_WIDTH / 2) 
		cameraPosition[0] = MAP_WIDTH - SCREEN_WIDTH / 2;
	if (cameraPosition[1] > MAP_HEIGHT - SCREEN_HEIGHT)
		cameraPosition[1] = MAP_HEIGHT - SCREEN_HEIGHT;


	/////////////////////////// CAMERA TWO ///////////////////////////////////////////////
	cameraTwoPosition[0] = -(SCREEN_WIDTH / 2 / 2) + (b->x + SPRITECELL / 2);
	cameraTwoPosition[1] = -(SCREEN_HEIGHT / 2) + (b->y + SPRITECELL / 2);

	//////// CAMERA MOVEMENT LIMITS
	if (cameraTwoPosition[0] < 0)
		cameraTwoPosition[0] = 0;
	if (cameraTwoPosition[1] < 0)
		cameraTwoPosition[1] = 0;

	if (cameraTwoPosition[0] > MAP_WIDTH - SCREEN_WIDTH / 2)
		cameraTwoPosition[0] = MAP_WIDTH - SCREEN_WIDTH / 2;
	if (cameraTwoPosition[1] > MAP_HEIGHT - SCREEN_HEIGHT)
		cameraTwoPosition[1] = MAP_HEIGHT - SCREEN_HEIGHT;
};

void Render::CameraTransform(){

	///////////////////// CAMERA ONE ///////////////////////
	al_identity_transform(&camera);
	al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
	//al_use_transform(&camera); // TAKEN OUT DUE TO IT MOVING THE PLAYER SCREENS

	///////////////////// CAMERA TWO ///////////////////////
	al_identity_transform(&cameraTwo);
	al_translate_transform(&cameraTwo, -cameraTwoPosition[0], -cameraTwoPosition[1]);
	//al_use_transform(&cameraTwo);  // TAKEN OUT DUE TO IT MOVING THE PLAYER SCREENS
};

void Render::DrawWords(int i, int j, int sec){ //// DRAW TEXT

	//// PLAYER ONE
	al_draw_text(wonderland, al_map_rgb(0, 0, 0), 15, 15, ALLEGRO_ALIGN_LEFT, "Player One");
	al_draw_textf(wonderland, al_map_rgb(0, 0, 0), 240, 15, ALLEGRO_ALIGN_LEFT, "%d", i);

	//// PLAYER TWO
	al_draw_text(wonderland, al_map_rgb(0, 0, 0), SCREEN_WIDTH / 2 + 15, 15, ALLEGRO_ALIGN_LEFT, "Player Two");
	al_draw_textf(wonderland, al_map_rgb(0, 0, 0), SCREEN_WIDTH - 100 + 10, 15, ALLEGRO_ALIGN_LEFT, "%d", j);

	//// TIME LEFT
	al_draw_textf(wonderland, al_map_rgb(0, 0, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, ALLEGRO_ALIGN_CENTER, "%d", sec);
};

void Render::EndGame(int i, int j, bool g){

	al_draw_text(wonderland, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 15, ALLEGRO_ALIGN_CENTER, "~ Game Over ~");

	//// PLAYER ONE
	al_draw_text(wonderland, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Player One");
	al_draw_textf(wonderland, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, ALLEGRO_ALIGN_CENTER, "%d", i);

	if (g == true){
		//// PLAYER TWO
		al_draw_text(wonderland, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTER, "Player Two");
		al_draw_textf(wonderland, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTER, "%d", j);
	}
};
