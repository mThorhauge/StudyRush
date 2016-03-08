#pragma once
#include "Game.h"
class TwoP :
	public Game
{
public:
	TwoP();
	~TwoP();


	void InitPlayers();
	void Run(ALLEGRO_DISPLAY * display);
	void Update();
	void Draw(ALLEGRO_DISPLAY * display);
	void GG();
};

