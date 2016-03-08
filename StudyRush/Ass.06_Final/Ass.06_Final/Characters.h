#pragma once

//////////////////////////// MY LIBRARIES
#include "Sprites.h"
#include "CharacterEnum.h"

class Character : public Sprites{

public:

	DIRECTIONS direction;			//// MOVEMENT DIRECTION
	CHARACTER type;					//// CHARACTER TYPE

	int speed;						//// MOVEMENT SPEED

	Character();
	~Character();

	void SetStatis(int type);		//// PLAYER ONE/SERVER || PLAYER TWO/CLIENT || AI/LIBRARIAN
};

