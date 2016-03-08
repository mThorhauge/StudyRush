//////////////////// MY LIBRARIES
#pragma once
#include "Characters.h"

class Librarians : public Character{

public:


	Librarians();
	~Librarians();

	void InitLibrarians();	        //// SET BITMAPS AND SPEED
	void MoveLibrarians();			//// MOVEMENT
	void CheckWalls();				//// CHECK FOR WALLS
};

