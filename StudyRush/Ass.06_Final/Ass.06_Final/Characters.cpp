#include "Characters.h"


Character::Character(){
	speed = 4;
	cellColoumb = 1;
	direction = STILL;
};

Character::~Character(){
};

void Character::SetStatis(int typeS){		//Set character's role
	// 1 || 2 || 3

	if (typeS == 1)
		type = SERVER;
	if (typeS == 2)
		type = CLIENT;
	if (typeS == 3)
		type = LIBRARIAN;

};
