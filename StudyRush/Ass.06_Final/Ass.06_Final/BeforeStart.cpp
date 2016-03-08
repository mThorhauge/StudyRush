#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h" //// IMAGE LOADING
#include "stdio.h"

#include "BeforeStart.h"

BeforeStart::BeforeStart(){

	gametype = ONEPLAYER; ////DEFAULT
	start = false;
	_title = true;
	_control = false;
	_story = false;

	////// LOAD SREENS
	screen = al_load_bitmap("Bitmaps/screen.bmp");
	title = al_load_bitmap("Bitmaps/title.png");
	name = al_load_bitmap("Bitmaps/name.png");
	control = al_load_bitmap("Bitmaps/controls.png");
	story = al_load_bitmap("Bitmaps/story.png");
	select = al_load_bitmap("Bitmaps/select.png");

	///// REGISTER MOUSE EVENTS
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
};

BeforeStart::~BeforeStart(){ ////DESTROY / DEALLOCATE MEMORY

	//al_destroy_bitmap(screen);
	//al_destroy_bitmap(title);
	//al_destroy_bitmap(name);
	//al_destroy_bitmap(control);
	//al_destroy_bitmap(story);
	//al_destroy_bitmap(select);
};

void BeforeStart::Run(){ //// RUN THE MENUE

	while (!start){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		al_get_keyboard_state(&key_state);
		al_get_mouse_state(&mouse_state);

		if (_title){
			al_draw_bitmap(screen, 0, 0, 0);
			TitleScreen();
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				_title = false;
				_select = true;
			}
			if (al_key_down(&key_state, ALLEGRO_KEY_SPACE)){
				_title = false;
				_select = true;
			}
		}
		if (_control){
			al_draw_bitmap(screen, 0, 0, 0);
			ControlsScreen();
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				_select = true;
				_control = false;
			}
			if (al_key_down(&key_state, ALLEGRO_KEY_SPACE)){
				_select = true;
				_control = false;
			}
		}
		if (_story){
			al_draw_bitmap(screen, 0, 0, 0);
			StoryScreen();
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				_select = true;
				_story = false;
			}
			if (al_key_down(&key_state, ALLEGRO_KEY_SPACE)){
				_select = true;
				_story = false;
			}
		}
		if (_select){
			al_draw_bitmap(screen, 0, 0, 0);
			SelectScreen();
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				if (mouse_state.buttons & 1){
					if (mouse_state.y > 261 && mouse_state.y < 316){
						if (mouse_state.x > 91 && mouse_state.x < 301 && _select){ //// ONE PLAYER GAME START
							gametype = ONEPLAYER;
							start = true;
						}
						if (mouse_state.x > 350 && mouse_state.x < 560 & _select){ //// TWO PLAYER GAME START
							gametype = TWOPLAYER;
							start = true;
						}
					}

					if (mouse_state.y > 340 && mouse_state.y < 394){
						if (mouse_state.x > 91 && mouse_state.x < 301 & _select){ //// CONTROLS SCREEN
							_control = true;
							_select = false;
						}
						if (mouse_state.x > 350 && mouse_state.x < 560 & _select){ //// STORY SCREEN
							_story = true;
							_select = false;
						}
					}
				}
			}
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ //// CLICK X ON WINDOW
				exit(0);
			}
		}
		al_flip_display();
	}

	if (start){
		Start();
	}
};

void BeforeStart::TitleScreen(){ //// TITLE SCREEN
	al_draw_bitmap(title, 166, 198, 0);
};

void BeforeStart::SelectScreen(){ //// SELECT NEXT
	al_draw_bitmap(select, 91, 260, 0);
	al_draw_bitmap(name, 25, 2, 0);
};

void BeforeStart::ControlsScreen(){ //// DISPLAY CONTROLS
	al_draw_bitmap(name, 25, 2, 0);
	al_draw_bitmap(control, 91, 241, 0);
};

void BeforeStart::StoryScreen(){  //// DISPLAY STORY / GAME CONCEPT
	al_draw_bitmap(name, 25, 2, 0);
	al_draw_bitmap(story, 90, 263, 0);
};

void BeforeStart::Start(){

	al_destroy_bitmap(screen);
	al_destroy_bitmap(title);
	al_destroy_bitmap(name);
	al_destroy_bitmap(control);
	al_destroy_bitmap(story);
	al_destroy_bitmap(select);
};