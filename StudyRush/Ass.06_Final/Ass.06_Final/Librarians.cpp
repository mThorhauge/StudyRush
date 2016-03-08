//////////////////////// MY LIBRARIES
#include "Librarians.h"
#include "Physics.h"

Librarians::Librarians(){
	//// DEFAULT VALUES
	speed = 4;
};

Librarians::~Librarians(){ //// DESTRUCTION OCCURES IN ~SPRITES()
};

void Librarians::InitLibrarians(){  //// INITIALIZE LIBRARIANS

		//// SET BITMAP
		sprite = al_load_bitmap("Bitmaps/enemy_character.bmp");

		//// SPEED BOST
		int extraSpeed = rand() % 4;
		speed = speed + extraSpeed;

		if (speed == 0) //// DON'T STAY IN ONE PLACE
			speed = 4;
};

void Librarians::MoveLibrarians(){ //// MOVEMENT

	if (direction == DOWN){
		y += speed;
		cellRow = 0;
		cellColoumb++;
		if (cellColoumb == 3)
			cellColoumb = 0;
		if (y > MAP_HEIGHT - SPRITECELL)
			direction = UP;	
	}

	if (direction == LEFT){
		x -= speed;
		cellRow = 1;
		cellColoumb++;
		if (cellColoumb == 3)
			cellColoumb = 0;
		if (x < 0)
			direction = RIGHT;
	}

	if (direction == RIGHT){
		x += speed;
		cellRow = 2;
		cellColoumb++;
		if (cellColoumb == 3)
			cellColoumb = 0;
		if (x > MAP_WIDTH - SPRITECELL)
			direction = LEFT;
	}

	if (direction == UP){
		y -= speed;
		cellRow = 3;
		cellColoumb++;
		if (cellColoumb == 3)
			cellColoumb = 0;
		if (y < 0)
			direction = DOWN;
	}
	CheckWalls();
};

void Librarians::CheckWalls(){ //// CHECK FOR WALLS

	if (y < SPRITECELL + 7)                         //// ROW 1
		direction = DOWN;

	if (y > 0 && y < SPRITECELL * 5 + 7){			//// ROWS 2 - 5
		if (x < SPRITECELL * 2 - 5){				//// COLOUMBS 1, 2
			if (direction == LEFT)
				direction = RIGHT;
			if (direction == UP)
				direction = DOWN;
		}
	}
	if (y > SPRITECELL * 3 && y < SPRITECELL * 7 + 7){ //// ROWS 4 - 7
		if (x < SPRITECELL - 5){					   //// COLOUMBS 1
			if (direction == LEFT)
				direction = RIGHT;
			if (direction == UP)
				direction = DOWN;
		}
	}
	if (y > SPRITECELL * 3 + 3 && y < SPRITECELL * 5 + 7){		//// ROWS 4, 5
		if (x > SPRITECELL * 3 + 5 && x < SPRITECELL * 10 - 7){ //// COLOUMBS 4 - 10
			if (direction == DOWN)
				direction = UP;
			else if (direction == UP)
				direction = DOWN;
			if (direction == RIGHT)
				direction = LEFT;
			else if (direction == LEFT)
				direction = RIGHT;
		}
	}
	if (y > SPRITECELL * 3 + 3 && y < SPRITECELL * 5 + 7){		//// ROWS 4, 5
		if (x > SPRITECELL * 11 + 5 && x < SPRITECELL * 18 - 7){//// COLOUMBS 12 - 18
			if (direction == DOWN)
				direction = UP;
			else if (direction == UP)
				direction = DOWN;
			if (direction == RIGHT)
				direction = LEFT;
			else if (direction == LEFT)
				direction = RIGHT;
		}
	}
	if (y > SPRITECELL && y < SPRITECELL * 6 + 7){		//// ROWS 2 - 6
		if (x > SPRITECELL * 22 + 7){					//// COLOUMBS 24, 25
			if (direction == RIGHT)
				direction = LEFT;
			if (direction == UP)
				direction = DOWN;
		}
	}
	if (y > SPRITECELL * 7 + 3 && y < SPRITECELL * 9 + 7){		//// ROWS 8, 9
		if (x > SPRITECELL * 6 + 5 && x < SPRITECELL * 19 - 7){ //// COLOUMBS 7 - 19
			if (direction == DOWN)
				direction = UP;
			else if (direction == UP)
				direction = DOWN;
			if (direction == RIGHT)
				direction = LEFT;
			else if (direction == LEFT)
				direction = RIGHT;
		}
	}
	if (y > SPRITECELL * 8 + 3){			//// ROWS 9 - 25
		if (x > SPRITECELL * 22 + 5){		//// COLOUMBS 24, 25
			if (direction == DOWN)
				direction = UP;
			if (direction == RIGHT)
				direction = LEFT;
		}
	}
	if (y > SPRITECELL * 10 + 3){		//// ROWS 11 - 25
		if (x < SPRITECELL * 2 - 7){	//// COLOUMBS 1, 2
			if (direction == DOWN)
				direction = UP;
			if (direction == LEFT)
				direction = RIGHT;
		}
	}
	if (y > SPRITECELL * 11 + 3 && y < SPRITECELL * 13 + 7){	//// ROWS 12, 13
		if (x < SPRITECELL * 8 - 7){							//// COLOUMBS 1 - 8
			if (direction == DOWN)
				direction = UP;
			else if (direction == UP)
				direction = DOWN;
			if (direction == LEFT)
				direction = RIGHT;
		}
	}
	if (y > SPRITECELL * 19 + 3 && y < SPRITECELL * 21 + 7){	//// ROWS 20, 21
		if (x < SPRITECELL * 8 - 7){							//// COLOUMBS 1 - 8
			if (direction == DOWN)
				direction = UP;
			else if (direction == UP)
				direction = DOWN;
			if (direction == LEFT)
				direction = RIGHT;
		}
	}
	if (y > SPRITECELL * 12 + 3 && y < SPRITECELL * 14 + 7){	//// ROWS 13, 14
		if (x > SPRITECELL * 14 + 5){							//// COLOUMBS 15 - 25
			if (direction == DOWN)
				direction = UP;
			else if (direction == UP)
				direction = DOWN;
			if (direction == RIGHT)
				direction = LEFT;
		}
	}
	if (y > SPRITECELL * 18 + 3 && y < SPRITECELL * 20 + 7){	//// ROWS 19, 20
		if (x > SPRITECELL * 20 + 5){							////COLOUMBS 21 - 25
			if (direction == DOWN)
				direction = UP;
			else if (direction == UP)
				direction = DOWN;
			if (direction == RIGHT)
				direction = LEFT;
		}
	}
	if (y > SPRITECELL * 22 + 3){					////ROWS 23 - 25
		if (x > SPRITECELL * 20 + 5){				//// COLOUMBS 20 - 25
			if (direction == DOWN)
				direction = UP;
			if (direction == RIGHT)
				direction = LEFT;
		}
	}
	if (y > SPRITECELL * 15 + 3 && y < SPRITECELL * 17 + 7){		//// ROS 16, 17
		if (x > SPRITECELL * 4 + 5 && x < SPRITECELL * 15 - 7){		//// COLOUMBS 5 - 15
			if (direction == DOWN)
				direction = UP;
			else if(direction == UP)
				direction = DOWN;
			if (direction == RIGHT)
				direction = LEFT;
			else if (direction == LEFT)
				direction = RIGHT;
		}
	}
	if (y > SPRITECELL * 19 + 3 && y < SPRITECELL * 21 + 7){		////ROWS 20, 21
		if (x > SPRITECELL * 9 + 5 && x < SPRITECELL * 16 - 7){		//// COLOUMBS 10 - 16
			if (direction == DOWN)
				direction = UP;
			else if (direction == UP)
				direction = DOWN;
			if (direction == RIGHT)
				direction = LEFT;
			else if (direction == LEFT)
				direction = RIGHT;
		}
	}
	if (y > SPRITECELL * 23 + 3)		 //// ROS 24, 25
		direction = UP;
};
