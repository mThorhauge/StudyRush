#pragma once

//////////////////////////////////ALLEGRO LIBRARIES
#include <allegro5/allegro_ttf.h>   
#include <allegro5/allegro_font.h>  

class Render
{
public:
	Render();
	~Render();

	float cameraPosition[2];                        //// PLAYER ONE CAMERA
	float cameraTwoPosition[2];                     //// PLAYER TWO CAMERA

	ALLEGRO_TRANSFORM camera;                       //// PLAYER ONE CAMERA
	ALLEGRO_TRANSFORM cameraTwo;                    //// PLAYER TWO CAMERA

	ALLEGRO_FONT * wonderland;						//// FONT

	void CameraUpdate(Player * a, Player * b);		//// ONE PLAYER GAMES
	void CameraTransform();

	void CameraUpdateTwo(Player * a);				//// TWO PLAYER GAMES
	void CameraTransformTwo();

	void Draw(Sprites * a);								//// DRAW THINGS (1 CELL X 1 CELL)
	void DrawObsticals(Sprites * a);					//// DRAW THINGS (1 CELL X 2 CELL)
	void DrawScreens(ALLEGRO_BITMAP * screen, ALLEGRO_BITMAP * screen2, ALLEGRO_BITMAP * split);  ////DRAW SPLIT SCREENS
	void DrawMessage(ALLEGRO_BITMAP * screen);			////DRAW GAME MESSAGES
	void Start(ALLEGRO_BITMAP* bg);						////DRAW MAP BITMAPS
	void End();											//// FLIP DISPLAY
	void Init();										//// INITIALIZE RENDER
	void DrawWords(int i, int j, int sec);				//// DRAW TEXT
	void DrawWordsTwo(int i, int sec);					//// DRAW TEXT
	void EndGame(int i, int j, bool g);					//// P1 SCORE P2 SCORE NUMPLAYERS
};

