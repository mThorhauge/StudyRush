#include "OneP.h"


OneP::OneP(){
}

OneP::~OneP(){
}

void OneP::InitPlayer(){

	////SET PLAYERS
	player.SetStatis(1);
	player.InitPlayer();
};

void OneP::Run(){


	Init(); ////INITIALIZE GAME OBJECTS, BITMAPS AND TIMERS
	InitPlayer();

	al_start_timer(frameRate); ////IMAGE FRAMS PER SECOND
	al_start_timer(timer);     ////FRAMS PER SECOND
	al_start_timer(timeLeft);  ////TIME LIMIT

	audio.PlayMusic();

	while (!quit){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.timer.source == timer){

			////UPDATE
			Update();

			render.CameraUpdateTwo(&player);
			render.CameraTransformTwo();
		}

		if (ev.timer.source == frameRate){

			////DRAW
			Draw();
		}

		if (al_get_timer_count(timeLeft) == TIME_LIMIT){
			quit = true;
		}

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ //// CLICK X ON WINDOW
			quit = true;
			end = true;
		}

		if (ev.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT){ //// SWITCH OUT / TAB / MINIMIZE GAME

			al_stop_timer(timer);
			audio.StopMusic();

			if (player.collied)
				al_stop_timer(respawn[0]);
			al_stop_timer(frameRate);
			al_stop_timer(timeLeft);
		}

		if (ev.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN){ //// SWITCH IN / TAB / MAXIMIZE GAME

			al_start_timer(timer);
			audio.PlayMusic();

			if (player.collied)
				al_start_timer(respawn[0]);

			al_start_timer(frameRate);
			al_start_timer(timeLeft);
		}

	}

	while (!end){
		GG();
		End();
	}

};

void OneP::Update(){

	////CHECK FOR RESPAWNS
	if (player.collied == true){
		if (al_get_timer_count(respawn[0]) == RESPAWN){
			al_stop_timer(respawn[0]);
			al_set_timer_count(respawn[0], 0);
			player.collied = false;
			audio.PlayRespawn();
		}
	}

	////MOVE PLAYERS
	PlayerControls();

	if (player.collied == false)
		player.MovePlayer();

	////COLLISION TESTING ~~ LIBRARIANS
	for (int i = 0; i < NUM_ENEMIES; i++){
		librarian[i].MoveLibrarians();

		if (!player.collied)
			player.collied = physics.PPCollision(&player, &librarian[i]);

		if (player.collied == true){
			al_start_timer(respawn[0]);
			player.x = 120;
			player.y = 320;
			audio.PlayCaught();
		}
	}

	////COLLISION TESTING ~~ BOOKS
	for (int i = 0; i < NUM_BOOKS; i++){
		if (!book[i].collied){
			book[i].collied = physics.PPCollision(&player, &book[i]); // COLLISION WITH PLAYER ONE
			if (book[i].collied && book[i].visible == 100){

				if (physics.PPCollision(&player, &book[i])){ //// PLAYER ONE
					player.score++;
					book[i].visible = 0;
				}

				audio.PlayCollect();
				SwapBooks(i);
			}
		}
	}
};

void OneP::Draw(){

		render.Start(background);				//FLOOR
		render.Start(StaticBookcase.sprite);	//BOOKCASES

		for (int i = 0; i < NUM_BOOKS; i++){	//BOOKS
			render.Draw(&book[i]);
		}
		for (int i = 0; i < NUM_ENEMIES; i++){	//LIBRARIANS
			render.Draw(&librarian[i]);
		}

		if (!player.collied)
			render.Draw(&player);

	int time = TIME_LIMIT - al_get_timer_count(timeLeft);
	render.DrawWordsTwo(player.score, time);

	render.End(); //FLIP DISPLAY
};

void OneP::GG(){
	
	render.DrawMessage(endScreen);
	render.EndGame(player.score, 0, false);
	render.End();
};
