#pragma once
#include "Game.h"
class OneP :
	public Game
{
public:

	OneP();
	~OneP();

	void InitPlayer();
	void Run();
	void Update();
	void Draw();
	void GG();
};

