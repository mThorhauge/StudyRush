#pragma once
#include "Characters.h"

class Player : public Character{

public:

	int score;				//// PLAYER SCORE (OBVIOUSLY)

	Sprites bookcases[NUM_BOOKCASES]; //// PLACEABLE BOOKCASES

	Player();
	~Player();

	void InitPlayer();      //// INITIALIZE STARTING POINTS
	void MovePlayer();		//// MOVEMENT
	void CheckWalls();		//// CHECK FOR WALLS

};

