////////////////////////////// ALLEGRO LIBRARIES
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h" // image loadin

///////////////////////////// MY LIBRARIES
#include "DefinedValues.h"
#pragma once
#include "DirectionEnum.h"

class Sprites {

public:

	//// GAME OBJECT VALUES
	int x;                                               //// X LOCATION
	int y;												 //// Y LOCATION
	int visible;										 //// VISIBILITY VALUE

	//// SPRITESHEET VALUES
	int cellRow;										 //// CELL ROW NUMBER
	int cellColoumb;									 //// CELL COLOUMB NUMBER

	//// COLLISION
	bool collied;										 //// COLLISION? YES || NO
	
	ALLEGRO_BITMAP * sprite;							 //// BITMAP

	Sprites();
	~Sprites();

	void InitBooks();									//// SET BOOK BITMAP
};