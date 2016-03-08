#include "Player.h"

Player::Player(){

};

Player::~Player(){
};

void Player::InitPlayer(){       //// INITIALIZE STARTING POINTS
	
	if (type == SERVER){   //////////// PLAYER ONE
		sprite = al_load_bitmap("Bitmaps/player_character.bmp");
		x = 120;
		y = 320;

		for (int i = 0; i < NUM_BOOKCASES; i++){
			bookcases[i].sprite = al_load_bitmap("Bitmaps/player_bookcase1.bmp");
		}
	}

	if (type == CLIENT){   /////////////// PLAYER TWO
		sprite = al_load_bitmap("Bitmaps/player_character2.bmp");
		x = 840;
		y = 320;

		for (int i = 0; i < NUM_BOOKCASES; i++){
			bookcases[i].sprite = al_load_bitmap("Bitmaps/player_bookcase2.bmp");
		}
	}
};

void Player::MovePlayer(){										//// MOVE

	if (direction == STILL){
		cellRow = 0;
		cellColoumb = 1;
	}

	if (direction == DOWN){										//// GOIN DOWN
		y += speed;
		if (y > MAP_HEIGHT - (SPRITECELL - 5))
			direction = UP;

		cellRow = 0;
		cellColoumb++;
		if (cellColoumb == 3){
			cellColoumb = 0;
		}
	}

	if (direction == LEFT){										//// GOIN LEFT
		x -= speed;
		if (x < -10)
			direction = RIGHT;

		cellRow = 1;
		cellColoumb++;
		if (cellColoumb == 3)
			cellColoumb = 0;
	}

	if (direction == RIGHT){									//// GOIN RIGHT
		if (x > MAP_WIDTH - (SPRITECELL - 5))
			direction = LEFT;
		else
			x += speed;
		cellRow = 2;
		cellColoumb++;
		if (cellColoumb == 3)
			cellColoumb = 0;

	}

	if (direction == UP){										//// GOIN UP
		if (y < 0)
			direction = DOWN;
		else
			y -= speed;
		cellRow = 3;
		cellColoumb++;
		if (cellColoumb == 3)
			cellColoumb = 0;

	}
	CheckWalls();
};

void Player::CheckWalls(){										//// WALLS

	if (y < SPRITECELL + 7)										//// ROW 1
		y = SPRITECELL + 7;

	if (y > 0 && y < SPRITECELL * 5 + 7){						//// ROWS 1 - 5
		if (x < SPRITECELL * 2 - 5){							//// COLOUMBS 1, 2
			if (direction == LEFT)
				x = SPRITECELL * 2 - 5;
			if (direction == UP)
				y = SPRITECELL * 5 + 7;
		}
	}
	if (y > SPRITECELL * 3 && y < SPRITECELL * 7 + 7){			//// ROWS 4 - 7
		if (x < SPRITECELL - 5){								//// COLOUMBS 1, 2
			if (direction == LEFT)
				x = SPRITECELL - 5;
			if (direction == UP)
				y = SPRITECELL * 7 + 7;
		}
	}
	if (y > SPRITECELL * 3 + 3 && y < SPRITECELL * 5 + 7){		//// ROWS 4, 5
		if (x > SPRITECELL * 3 + 5 && x < SPRITECELL * 10 - 7){ //// COLOUMBS 4 - 10
			if (direction == DOWN)
				y = SPRITECELL * 3 + 3;
			if (direction == UP)
				y = SPRITECELL * 5 + 7;
			if (direction == RIGHT)
				x = SPRITECELL * 3 + 5;
			if (direction == LEFT)
				x = SPRITECELL * 10 - 7;
		}
	}
	if (y > SPRITECELL * 3 + 3 && y < SPRITECELL * 5 + 7){		//// ROWS 4, 5
		if (x > SPRITECELL * 11 + 5 && x < SPRITECELL * 18 - 7){//// COLOUMBS 12 - 18
			if (direction == DOWN)
				y = SPRITECELL * 3 + 3;
			if (direction == UP)
				y = SPRITECELL * 5 + 7;
			if (direction == RIGHT)
				x = SPRITECELL * 11 + 5;
			if (direction == LEFT)
				x = SPRITECELL * 18 - 7;
		}
	}
	if (y > SPRITECELL && y < SPRITECELL * 6 + 7){				//// ROWS 2 - 6
		if (x > SPRITECELL * 22 + 7){							//// COLOUMBS 24, 25
			if (direction == RIGHT)
				x = SPRITECELL * 22 + 7;
			if (direction == UP)
				y = SPRITECELL * 6 + 7;
		}
	}
	if (y > SPRITECELL * 7 + 3 && y < SPRITECELL * 9 + 7){		//// ROWS 8, 9
		if (x > SPRITECELL * 6 + 5 && x < SPRITECELL * 19 - 7){ //// COLOUMBS 7 - 19
			if (direction == DOWN)
				y = SPRITECELL * 7 + 3;
			if (direction == UP)
				y = SPRITECELL * 9 + 7;
			if (direction == RIGHT)
				x = SPRITECELL * 6 + 5;
			if (direction == LEFT)
				x = SPRITECELL * 19 - 7;
		}
	}
	if (y > SPRITECELL * 8 + 3 ){                              //// ROWS 9 - 25
		if (x > SPRITECELL * 22 + 5){						   //// COLOUMBS 24, 25
			if (direction == DOWN)
				y = SPRITECELL * 8 + 3;
			if (direction == RIGHT)
				x = SPRITECELL * 22 + 5;
		}
	}
	if (y > SPRITECELL * 10 + 3){								//// ROWS 11 - 25
		if (x < SPRITECELL * 2 - 7){							//// COLOUMBS 1, 2
			if (direction == DOWN)
				y = SPRITECELL * 10 + 3;
			if (direction == LEFT)
				x = SPRITECELL * 2 - 7;
		}
	}
	if (y > SPRITECELL * 11 + 3 && y < SPRITECELL * 13 + 7){	//// ROWS 12, 13
		if (x < SPRITECELL * 8 - 7){							//// COLOUMBS 1 - 8
			if (direction == DOWN)
				y = SPRITECELL * 11 + 3;
			if (direction == UP)
				y = SPRITECELL * 13 + 7;
			if (direction == LEFT)
				x = SPRITECELL * 8 - 7;
		}
	}
	if (y > SPRITECELL * 19 + 3 && y < SPRITECELL * 21 + 7){	//// ROWS 20, 21
		if (x < SPRITECELL * 8 - 7){							//// COLOUMBS 1 - 8
			if (direction == DOWN)
				y = SPRITECELL * 19 + 3;
			if (direction == UP)
				y = SPRITECELL * 21 + 7;
			if (direction == LEFT)
				x = SPRITECELL * 8 - 7;
		}
	}
	if (y > SPRITECELL * 12 + 3 && y < SPRITECELL * 14 + 7){	//// ROWS 13, 14
		if (x > SPRITECELL * 14 + 5){							//// COLOUMBS 15 - 25
			if (direction == DOWN)
				y = SPRITECELL * 12 + 3;
			if (direction == UP)
				y = SPRITECELL * 14 + 7;
			if (direction == RIGHT)
				x = SPRITECELL * 14 + 5;
		}
	}
	if (y > SPRITECELL * 18 + 3 && y < SPRITECELL * 20 + 7){	//// ROWS 19,20
		if (x > SPRITECELL * 20 + 5){							//// COLOUMBS 21 - 25
			if (direction == DOWN)
				y = SPRITECELL * 18 + 3;
			if (direction == UP)
				y = SPRITECELL * 20 + 7;
			if (direction == RIGHT)
				x = SPRITECELL * 20 + 5;
		}
	}
	if (y > SPRITECELL * 22 + 3){								//// ROWS 23 - 25
		if (x > SPRITECELL * 20 + 5){							//// COLOUMBS 20 - 25
			if (direction == DOWN)
				y = SPRITECELL * 22 + 3;
			if (direction == RIGHT)
				x = SPRITECELL * 20 + 5;
		}
	}
	if (y > SPRITECELL * 15 + 3 && y < SPRITECELL * 17 + 7){	//// ROWS 16, 17
		if (x > SPRITECELL * 3 + 5 && x < SPRITECELL * 15 - 7){ //// COLOUMBS 4 - 15
			if (direction == DOWN)
				y = SPRITECELL * 15 + 3;
			if (direction == UP)
				y = SPRITECELL * 17 + 7;
			if (direction == RIGHT)
				x = SPRITECELL * 3 + 5;
			if (direction == LEFT)
				x = SPRITECELL * 15 - 7;
		}
	}
	if (y > SPRITECELL * 19 + 3 && y < SPRITECELL * 21 + 7){	//// ROWS 20, 21
		if (x > SPRITECELL * 9 + 5 && x < SPRITECELL * 16 - 7){ //// COLOUMBS 10 - 16
			if (direction == DOWN)
				y = SPRITECELL * 19 + 3;
			if (direction == UP)
				y = SPRITECELL * 21 + 7;
			if (direction == RIGHT)
				x = SPRITECELL * 9 + 5;
			if (direction == LEFT)
				x = SPRITECELL * 16 - 7;
		}
	}
	if (y > SPRITECELL * 23 + 3)								//// ROWS 24, 25
		y = SPRITECELL * 23 + 3;
};
