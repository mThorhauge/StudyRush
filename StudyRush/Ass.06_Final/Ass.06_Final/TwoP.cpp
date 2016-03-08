#include "TwoP.h"


TwoP::TwoP(){
};


TwoP::~TwoP(){
};

void TwoP::InitPlayers(){
	
	////SET PLAYERS
	player.SetStatis(1);
	player.InitPlayer();

	playerTwo.SetStatis(2);
	playerTwo.InitPlayer();
};

void TwoP::Run(ALLEGRO_DISPLAY * display){


	Init(); ////INITIALIZE GAME OBJECTS, BITMAPS AND TIMERS
	InitPlayers();

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

			render.CameraUpdate(&player, &playerTwo);
			render.CameraTransform();
		}

		if (ev.timer.source == frameRate){

			////DRAW
			Draw(display);
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
			if (playerTwo.collied)
				al_stop_timer(respawn[1]);
			al_stop_timer(frameRate);
			al_stop_timer(timeLeft);
		}

		if (ev.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN){ //// SWITCH IN / TAB / MAXIMIZE GAME

			al_start_timer(timer);
			audio.PlayMusic();

			if (player.collied)
				al_start_timer(respawn[0]);

			if (playerTwo.collied)
				al_start_timer(respawn[1]);

			al_start_timer(frameRate);
			al_start_timer(timeLeft);
		}

	}

	while (!end){
		GG();
		End();
	}

};

void TwoP::Update(){

	////CHECK FOR RESPAWNS
	if (player.collied == true){
		if (al_get_timer_count(respawn[0]) == RESPAWN){
			al_stop_timer(respawn[0]);
			al_set_timer_count(respawn[0], 0);
			player.collied = false;
			audio.PlayRespawn();
		}
	}

	if (playerTwo.collied == true){
		if (al_get_timer_count(respawn[1]) == RESPAWN){
			al_stop_timer(respawn[1]);
			al_set_timer_count(respawn[1], 0);
			playerTwo.collied = false;
			audio.PlayRespawn();
		}
	}

	////MOVE PLAYERS
	PlayerControls();
	PlayerTwoControls();

	if (player.collied == false)
		player.MovePlayer();
	if (playerTwo.collied == false)
		playerTwo.MovePlayer();

	////COLLISION TESTING ~~ LIBRARIANS
	for (int i = 0; i < NUM_ENEMIES; i++){
		librarian[i].MoveLibrarians();

		if (!player.collied)
			player.collied = physics.PPCollision(&player, &librarian[i]);
		if (!playerTwo.collied)
			playerTwo.collied = physics.PPCollision(&playerTwo, &librarian[i]);

		if (player.collied == true){
			al_start_timer(respawn[0]);
			player.x = 120;
			player.y = 320;
			audio.PlayCaught();
		}
		if (playerTwo.collied == true){
			al_start_timer(respawn[1]);
			playerTwo.x = 840;
			playerTwo.y = 320;
			audio.PlayCaught();
		}
	}

	////COLLISION TESTING ~~ BOOKS
	for (int i = 0; i < NUM_BOOKS; i++){
		if (!book[i].collied){
			book[i].collied = physics.PPCollision(&player, &book[i]) || physics.PPCollision(&playerTwo, &book[i]); // COLLISION WITH PLAYER ONE OR TWO
			if (book[i].collied && book[i].visible == 100){

				if (physics.PPCollision(&player, &book[i])){ //// PLAYER ONE
					player.score++;
					book[i].visible = 0;
				}
				if (physics.PPCollision(&playerTwo, &book[i])){ ////PLAYER TWO
					playerTwo.score++;
					book[i].visible = 0;
				}

				audio.PlayCollect();
				SwapBooks(i);
			}
		}
	}
};

void TwoP::Draw(ALLEGRO_DISPLAY * display){

	ALLEGRO_BITMAP * subBitmap = NULL;

	for (int j = 0; j < 2; j++){

		al_set_target_bitmap(screen[j]); //SPECIFY PLAYER ONE OR TWO

		if (j == 0){ // PLAYER ONE SCREEN
			subBitmap = al_create_sub_bitmap(player.sprite, player.x, player.y, SPRITECELL, SPRITECELL);
			al_use_transform(&render.camera);
			render.Draw(&player);
		}

		else{ //PLAYER TWO SCREEN
			subBitmap = al_create_sub_bitmap(playerTwo.sprite, playerTwo.x, playerTwo.y, SPRITECELL, SPRITECELL);
			al_use_transform(&render.cameraTwo);
			render.Draw(&playerTwo);
		}

		render.Start(background);				//FLOOR
		render.Start(StaticBookcase.sprite);	//BOOKCASES

		for (int i = 0; i < NUM_BOOKS; i++){	//BOOKS
			render.Draw(&book[i]);
		}
		for (int i = 0; i < NUM_ENEMIES; i++){	//LIBRARIANS
			render.Draw(&librarian[i]);
		}

		if (player.y < playerTwo.y){			//PLAYER TWO IN FRONT
			if (!player.collied)
				render.Draw(&player);
			if (!playerTwo.collied)
				render.Draw(&playerTwo);
		}
		else{									//PLAYER ONE IN FRONT
			if (!playerTwo.collied)
				render.Draw(&playerTwo);
			if (!player.collied)
				render.Draw(&player);
		}
	}

	al_set_target_bitmap(al_get_backbuffer(display));		 //RETURN TO BUFFER
	render.DrawScreens(screen[0], screen[1], SplitScreen);	 //DRAW PLAYER SCREENS AND GAME BORDER

	int time = TIME_LIMIT - al_get_timer_count(timeLeft);

	render.DrawWords(player.score, playerTwo.score, time);

	render.End(); //FLIP DISPLAY

	al_clear_to_color(al_map_rgb(0, 0, 0)); // CLEAR JUST IN CASE
	al_destroy_bitmap(subBitmap);			//DESTROY UNNEEDED THINGS
};

void TwoP::GG(){

	render.DrawMessage(endScreen);
	render.EndGame(player.score, playerTwo.score, true);
	render.End();
};
