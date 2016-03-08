////////////////////////////////////// ALLEGRO AND COMM3ON LIBRARIES
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h" //// IMAGE LOADING
#include "stdio.h"

////////////////////////////////////// MY FILES
#include "Sprites.h"
#include "Player.h"
#include "Librarians.h"
#include "DefinedValues.h"
#include "Game.h"
#include "Render.h"
#include "Audio.h"

Game::Game(){

	//// SEED RANDOMIZER
	srand(time(NULL));

	//// TIMERS
	timer = NULL;
	frameRate = NULL;
	timeLeft = NULL;
	
	for (int i = 0; i < 2; i++)
		respawn[i] = NULL;

	event_queue = al_create_event_queue();

	//// PLAYER SCREENS
	for (int i = 0; i < 2; i++)
		screen[i] = al_create_bitmap(SCREEN_WIDTH / 2, SCREEN_HEIGHT);

	fprintf(stderr, "Game::Game()\n");
};

Game::~Game(){ //// DESTROY / DEALLOCATE USED MEMORY

	////BITMAPS
	al_destroy_bitmap(background);
	al_destroy_bitmap(endScreen);
	al_destroy_bitmap(SplitScreen);

	//TIMERS
	al_destroy_timer(frameRate);
	al_destroy_timer(timer);
	al_destroy_timer(timeLeft);

	for (int i = 0; i < 2; i++)
		al_destroy_timer(respawn[i]);

	al_destroy_event_queue(event_queue);

	fprintf(stderr, "Game::~Game()\n");
};

void Game::PlaceBooks(){                          // SET X, Y, AND BITMAP

	for (int i = 0; i < NUM_BOOKS; i++){
		book[i].InitBooks();
		book[i].collied = false;

		if (i < NUM_BOOKS / 3)
			book[i].visible = 100;
		else
			book[i].visible = 0;
	}

	book[0].x = SPRITECELL * 2;
	book[0].y = SPRITECELL * 2;

	book[1].x = SPRITECELL * 11;
	book[1].y = SPRITECELL * 15;

	book[2].x = SPRITECELL * 14;
	book[2].y = SPRITECELL * 7;

	book[3].x = SPRITECELL * 2;
	book[3].y = SPRITECELL * 19;

	book[4].x = SPRITECELL * 22;
	book[4].y = SPRITECELL * 15;

	book[5].x = SPRITECELL * 10;
	book[5].y = SPRITECELL * 4;

	book[6].x = SPRITECELL * 22;
	book[6].y = SPRITECELL * 22;

	book[7].x = SPRITECELL * 22;
	book[7].y = SPRITECELL * 2;

	book[8].x = SPRITECELL * 8;
	book[8].y = SPRITECELL * 20;

	book[9].x = SPRITECELL * 22;
	book[9].y = SPRITECELL * 18;

	book[10].x = SPRITECELL * 2;
	book[10].y = SPRITECELL * 22;

	book[11].x = SPRITECELL * 13;
	book[11].y = SPRITECELL * 2;

	book[12].x = SPRITECELL * 13;
	book[12].y = SPRITECELL * 17;

	book[13].x = SPRITECELL * 18;
	book[13].y = SPRITECELL * 12;

	book[14].x = SPRITECELL * 4;
	book[14].y = SPRITECELL * 8;

}

void Game::PlaceLibrarians(){                        // SET X, Y, BITMAP, AND DIRECTION

	for (int i = 0; i < NUM_ENEMIES; i++){
		librarian[i].SetStatis(3);
		librarian[i].InitLibrarians();
	}

	librarian[0].x = SPRITECELL * 10;
	librarian[0].y = SPRITECELL * 6;
	librarian[0].direction = UP;

	librarian[1].x = SPRITECELL * 8;
	librarian[1].y = SPRITECELL * 12;
	librarian[1].direction = DOWN;

	librarian[2].x = SPRITECELL * 19;
	librarian[2].y = SPRITECELL * 11;
	librarian[2].direction = UP;

	librarian[3].x = SPRITECELL * 15;
	librarian[3].y = SPRITECELL * 17;
	librarian[3].direction = RIGHT;

	librarian[4].x = SPRITECELL * 8;
	librarian[4].y = SPRITECELL * 22;
	librarian[4].direction = UP;

	librarian[5].x = SPRITECELL * 20;
	librarian[5].y = SPRITECELL * 19;
	librarian[5].direction = DOWN;

	librarian[6].x = SPRITECELL * 5;
	librarian[6].y = SPRITECELL * 2;
	librarian[6].direction = RIGHT;

	librarian[7].x = SPRITECELL * 15;
	librarian[7].y = SPRITECELL * 22;
	librarian[7].direction = LEFT;

	librarian[8].x = SPRITECELL * 7;
	librarian[8].y = SPRITECELL * 15;
	librarian[8].direction = LEFT;

	librarian[9].x = SPRITECELL * 2;
	librarian[9].y = SPRITECELL * 14;
	librarian[9].direction = DOWN;
}

void Game::SwapBooks(int booknum){                                      // ONE BOOK DISAPPEARS, ANOTHER APPEARS

	//////////////////////////////////////////// 1, 6, 11
	if (booknum == 0){
		book[5].visible = 100;
		book[5].collied = false;
	}
	if (booknum == 5){
		book[10].visible = 100;
		book[10].collied = false;
	}
	if (booknum == 10){
		book[0].visible = 100;
		book[0].collied = false;
	}

	//////////////////////////////////////////// 2, 7, 12

	if (booknum == 1){
		book[6].collied = false;
		book[6].visible = 100;
	}
	if (booknum == 6){
		book[11].collied = false;
		book[11].visible = 100;
	}
	if (booknum == 11){
		book[1].collied = false;
		book[1].visible = 100;
	}

	//////////////////////////////////////////// 3, 8, 13

	if (booknum == 2){
		book[7].collied = false;
		book[7].visible = 100;
	}
	if (booknum == 7){
		book[12].collied = false;
		book[12].visible = 100;
	}
	if (booknum == 12){
		book[2].collied = false;
		book[2].visible = 100;
	}

	//////////////////////////////////////////// 4, 9, 14

	if (booknum == 3){
		book[8].collied = false;
		book[8].visible = 100;
	}
	if (booknum == 8){
		book[13].collied = false;
		book[13].visible = 100;
	}
	if (booknum == 13){
		book[3].collied = false;
		book[3].visible = 100;
	}

	//////////////////////////////////////////// 5, 10, 15


	if (booknum == 4){
		book[9].collied = false;
		book[9].visible = 100;
	}
	if (booknum == 9){
		book[14].collied = false;
		book[14].visible = 100;
	}
	if (booknum == 14){
		book[4].collied = false;
		book[4].visible = 100;
	}

} 

void Game::Init(){

	quit = false;
	end = false;

	////SET TIMERS, ADD TO EVENT QUEUE
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	frameRate = al_create_timer(1.0 / FRAMERATE);
	al_register_event_source(event_queue, al_get_timer_event_source(frameRate));

	timeLeft = al_create_timer(1.0);
	al_register_event_source(event_queue, al_get_timer_event_source(timeLeft));

	for (int i = 0; i < 2; i++){
		respawn[i] = al_create_timer(1.0);
		al_register_event_source(event_queue, al_get_timer_event_source(respawn[i]));
	}

	////SET BITMAPS
	background = al_load_bitmap("Bitmaps/background.jpg");
	endScreen = al_load_bitmap("Bitmaps/screen.bmp");
	SplitScreen = al_load_bitmap("Bitmaps/split.png");

	////SET BOOKCASES
	StaticBookcase.x = 0;
	StaticBookcase.y = 0;
	StaticBookcase.sprite = al_load_bitmap("Bitmaps/bookcaseMap.png");

	////SET LIBRARIANAS
	PlaceLibrarians();
	PlaceBooks();

	//////SET PLAYERS       MOVED TO CHILD CLASSES
	//player.SetStatis(1);
	//player.InitPlayer();

	//playerTwo.SetStatis(2);
	//playerTwo.InitPlayer();

	fprintf(stderr, "Game::Init()\n");
};

void Game::PlayerControls(){ //// KEY INPUT

	ALLEGRO_KEYBOARD_STATE key_state;
	al_get_keyboard_state(&key_state);

	if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE)){
		quit = true;
		end = true;
	}

	if (al_key_down(&key_state, ALLEGRO_KEY_DOWN)) {
		player.direction = DOWN;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT)) {
		player.direction = LEFT;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) {
		player.direction = RIGHT;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_UP)) {
		player.direction = UP;
	}
	else {
		player.direction = STILL;
	}
};

void Game::PlayerTwoControls(){ //// KEY INPUT

	ALLEGRO_KEYBOARD_STATE key_state;
	al_get_keyboard_state(&key_state);

	if (al_key_down(&key_state, ALLEGRO_KEY_S)) {
		playerTwo.direction = DOWN;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_A)) {
		playerTwo.direction = LEFT;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_D)) {
		playerTwo.direction = RIGHT;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_W)) {
		playerTwo.direction = UP;
	}
	else {
		playerTwo.direction = STILL;
	}
};

void Game::End(){ ////GAME OVER

	ALLEGRO_KEYBOARD_STATE key_state;
	al_get_keyboard_state(&key_state);

	//al_convert_mask_to_alpha(endScreen, al_map_rgb(255, 0, 255)); //// FIX UP DEFAULT END GAME MESSAGE
	//render.DrawMessage(endScreen);								  //// DRAW END GAME MESSAGE
	//al_flip_display();

	audio.StopMusic();
	audio.PlayEndGame();

	if (al_key_down(&key_state, ALLEGRO_KEY_SPACE)) { //// REPLAY OPTION
		Destroy();									  //// STOP TIMERS
		end = true;	
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_ENTER)){ //// EXIT/CLOSE PROGRAM
		Destroy();										  //// STOP TIMERS
		end = true;	
	}
};

void Game::Destroy(){ ////STOP TIMERS 
	////ALL DESTROY ACTIONS MOVED TO ~GAME(){}

	al_stop_timer(frameRate);
	al_stop_timer(timer);
	al_stop_timer(timeLeft);
};

////// MOVED TO CHILD CLASSES
//void Game::Update(){
//
//	////CHECK FOR RESPAWNS
//	if (player.collied == true){
//		if (al_get_timer_count(respawn[0]) == RESPAWN){
//			al_stop_timer(respawn[0]);
//			al_set_timer_count(respawn[0], 0);
//			player.collied = false;
//			audio.PlayRespawn();
//		}
//	}
//
//	if (playerTwo.collied == true){
//		if (al_get_timer_count(respawn[1]) == RESPAWN){
//			al_stop_timer(respawn[1]);
//			al_set_timer_count(respawn[1], 0);
//			playerTwo.collied = false;
//			audio.PlayRespawn();
//		}
//	}
//
//	////MOVE PLAYERS
//	PlayerControls();
//	PlayerTwoControls();
//
//	if (player.collied == false)
//		player.MovePlayer();
//	if (playerTwo.collied == false)
//		playerTwo.MovePlayer();
//
//	////COLLISION TESTING ~~ LIBRARIANS
//	for (int i = 0; i < NUM_ENEMIES; i++){
//		librarian[i].MoveLibrarians();
//
//		if (!player.collied)
//			player.collied = physics.PPCollision(&player, &librarian[i]);
//		if (!playerTwo.collied)
//			playerTwo.collied = physics.PPCollision(&playerTwo, &librarian[i]);
//
//		if (player.collied == true){
//			al_start_timer(respawn[0]);
//			player.x = 120;
//			player.y = 320;
//			audio.PlayCaught();
//		}
//		if (playerTwo.collied == true){
//			al_start_timer(respawn[1]);
//			playerTwo.x = 840;
//			playerTwo.y = 320;
//			audio.PlayCaught();
//		}
//	}
//
//	////COLLISION TESTING ~~ BOOKS
//	for (int i = 0; i < NUM_BOOKS; i++){
//		if (!book[i].collied){														
//			book[i].collied = physics.PPCollision(&player, &book[i]) || physics.PPCollision(&playerTwo, &book[i]); // COLLISION WITH PLAYER ONE OR TWO
//			if (book[i].collied && book[i].visible == 100){							
//				
//				if (physics.PPCollision(&player, &book[i])){ //// PLAYER ONE
//					player.score++;
//					book[i].visible = 0;
//				}
//				if (physics.PPCollision(&playerTwo, &book[i])){ ////PLAYER TWO
//					playerTwo.score++;
//					book[i].visible = 0;
//				}
//
//				audio.PlayCollect();
//				SwapBooks(i);
//			}
//		}
//	}
//};
//
//void Game::Draw(ALLEGRO_DISPLAY * display){ // DRAW
//
//	ALLEGRO_BITMAP * subBitmap = NULL;
//
//	for (int j = 0; j < 2; j++){
//
//		al_set_target_bitmap(screen[j]); //SPECIFY PLAYER ONE OR TWO
//
//		if (j == 0){ // PLAYER ONE SCREEN
//			subBitmap = al_create_sub_bitmap(player.sprite, player.x, player.y, SPRITECELL, SPRITECELL);
//			al_use_transform(&render.camera);
//			render.Draw(&player);
//		}
//
//		else{ //PLAYER TWO SCREEN
//			subBitmap = al_create_sub_bitmap(playerTwo.sprite, playerTwo.x, playerTwo.y, SPRITECELL, SPRITECELL);
//			al_use_transform(&render.cameraTwo);
//			render.Draw(&playerTwo);
//		}
//
//		render.Start(background);				//FLOOR
//		render.Start(StaticBookcase.sprite);	//BOOKCASES
//
//		for (int i = 0; i < NUM_BOOKS; i++){	//BOOKS
//			render.Draw(&book[i]);
//		}
//		for (int i = 0; i < NUM_ENEMIES; i++){	//LIBRARIANS
//			render.Draw(&librarian[i]);
//		}
//
//		if (player.y < playerTwo.y){			//PLAYER TWO IN FRONT
//			if(!player.collied)
//				render.Draw(&player);
//			if (!playerTwo.collied)
//				render.Draw(&playerTwo);
//		}
//		else{									//PLAYER ONE IN FRONT
//			if (!playerTwo.collied)
//				render.Draw(&playerTwo);
//			if (!player.collied)
//				render.Draw(&player);
//		}
//	}
//
//	al_set_target_bitmap(al_get_backbuffer(display));		 //RETURN TO BUFFER
//	render.DrawScreens(screen[0], screen[1], SplitScreen);	 //DRAW PLAYER SCREENS AND GAME BORDER
//
//	int time = TIME_LIMIT - al_get_timer_count(timeLeft);
//
//	render.DrawWords(player.score, playerTwo.score, time);
//
//	render.End(); //FLIP DISPLAY
//
//	al_clear_to_color(al_map_rgb(0, 0, 0)); // CLEAR JUST IN CASE
//	al_destroy_bitmap(subBitmap);			//DESTROY UNNEEDED THINGS
//};
//
//void Game::Run(ALLEGRO_DISPLAY * display){
//
//	Init(); ////INITIALIZE GAME OBJECTS, BITMAPS AND TIMERS
//
//	al_start_timer(frameRate); ////IMAGE FRAMS PER SECOND
//	al_start_timer(timer);     ////FRAMS PER SECOND
//	al_start_timer(timeLeft);  ////TIME LIMIT
//
//	audio.PlayMusic();
//
//	while (!quit){
//		ALLEGRO_EVENT ev;
//		al_wait_for_event(event_queue, &ev);
//
//		if (ev.timer.source == timer){
//
//			////UPDATE
//			Update();
//
//			render.CameraUpdate(&player, &playerTwo);
//			render.CameraTransform();
//		}
//
//		if (ev.timer.source == frameRate){
//
//				////DRAW
//				Draw(display);	
//		}
//
//		if (al_get_timer_count(timeLeft) == TIME_LIMIT){
//			quit = true;
//		}
//
//		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ //// CLICK X ON WINDOW
//			quit = true;
//			end = true;
//		}
//
//		if (ev.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT){ //// SWITCH OUT / TAB / MINIMIZE GAME
//
//			al_stop_timer(timer);
//			audio.StopMusic();
//
//			if (player.collied)
//				al_stop_timer(respawn[0]);
//			if (playerTwo.collied)
//				al_stop_timer(respawn[1]);
//			al_stop_timer(frameRate);
//			al_stop_timer(timeLeft);
//		}
//
//		if (ev.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN){ //// SWITCH IN / TAB / MAXIMIZE GAME
//			
//			al_start_timer(timer);
//			audio.PlayMusic();
//
//			if (player.collied)
//				al_start_timer(respawn[0]);
//
//			if (playerTwo.collied)
//				al_start_timer(respawn[1]);
//
//			al_start_timer(frameRate);
//			al_start_timer(timeLeft);
//		}
//		
//	}
//
//	while (!end){
//		End();
//	}
//};

