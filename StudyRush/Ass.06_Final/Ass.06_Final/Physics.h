#pragma once
#include "Sprites.h"
#include "Characters.h"

class Physics{

public:
	Physics();
	~Physics();

	float Distance(Sprites * a, Sprites * b);					 //// DISTANCE EQUATION

	bool PPCollision(Sprites * a, Sprites * b);                  //// PIXEL PERFECT COLLISION
	bool BBCollision(int x1, int y1, int x2, int y2);            //// BOUNDING BOX COLLISION
};

