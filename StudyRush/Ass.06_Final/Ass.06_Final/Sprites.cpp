#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h" // image loadin
#include "stdio.h"

#include "Sprites.h"
#include "Physics.h"
#include "DefinedValues.h"

Sprites::Sprites(){

	//// DEFAULT VALUES
		x = 0;												
		y = 0;												
		cellRow = 0;										
		cellColoumb = 0;									
		visible = 100;
		collied = false;	

		fprintf(stderr, "Sprites::Sprites()\n");
};

Sprites::~Sprites(){ //// DESTROY / DEALLOCATE MEMORY
		al_destroy_bitmap(sprite);							
		fprintf(stderr, "Sprites::~Sprites()\n");
};

void Sprites::InitBooks(){ //// SET BITMAP

	sprite = al_load_bitmap("Bitmaps/Book_Collectible.bmp");
};
