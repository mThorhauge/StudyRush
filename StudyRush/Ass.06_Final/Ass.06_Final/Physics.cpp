//////////////////////////// MY LIBRARIES
#include "Physics.h"
/////////////////////////// COMMON LIBRARIES
#include <math.h>

Physics::Physics(){
};

Physics::~Physics(){
};

float Physics::Distance(Sprites * a, Sprites * b){ //// DISTANCE FORMULA
	float dis;

	float xCombo = (a->x - b->x)*(a->x - b->x);
	float yCombo = (a->y - b->y)*(a->y - b->y);

	dis = sqrt(xCombo + yCombo);

	return dis;
};

bool Physics::PPCollision(Sprites * a, Sprites * b){ //// PIXEL PERFECT COLLISION DETECTION

	int top, bottom, left, right; 

	//// CHECK FOR OVERLAP
	if (a->x + SPRITECELL < b->x || a->x > b->x + SPRITECELL ||
		a->y + SPRITECELL < b->y || a->y > b->y + SPRITECELL) {
		return false;
	}
	else { //// IF OVERLAPPING

		//// DETERMINE OVERLAPPING SECTION
		top = max(a->y, b->y); 
		bottom = min(a->y + SPRITECELL, b->y + SPRITECELL);
		left = max(a->x, b->x);
		right = min(a->x + SPRITECELL, b->x + SPRITECELL);

		for (int i = top; i < bottom; i++){
			for (int j = left; j < right; j++){ 

				///// DETERMINE COLOURED PIXEL COLLISION
				al_lock_bitmap(a->sprite, al_get_bitmap_format(a->sprite), ALLEGRO_LOCK_READONLY);
				al_lock_bitmap(b->sprite, al_get_bitmap_format(b->sprite), ALLEGRO_LOCK_READONLY);
				ALLEGRO_COLOR colour = al_get_pixel(a->sprite, j - a->x, i - a->y);
				ALLEGRO_COLOR colourE = al_get_pixel(b->sprite, j - b->x, i - b->y);

				//// IF COLLIDED
				if (colour.a != 0 && colourE.a != 0){ 
					return true; 
				}
			}
		}
	}
	return false;
};

bool Physics::BBCollision(int x1, int y1, int x2,int y2){ //// BOUNDING BOX COLLISION DETECTION

	//// IF NOT OVERLAPPING
	if (x1 + SPRITECELL < x2 ||
		x1 > x2 + SPRITECELL ||
		y1 + SPRITECELL < y2 ||
		y1 > y2 + SPRITECELL){
		return false;
	}
	else
		return true;
};
 