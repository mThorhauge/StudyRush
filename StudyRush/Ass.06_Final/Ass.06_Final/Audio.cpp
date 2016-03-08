/////////////////////////////// ALLEGRO LIBRARIES
#include "allegro5/allegro.h"
#include <allegro5/allegro_audio.h>	 //// AUDIO
#include <allegro5/allegro_acodec.h> //// CODEC AUDIO

/////////////////////////////// MY LIBRARIES
#include "Audio.h"

Audio::Audio(){

	MusicInstance = NULL;
	Init();
};

Audio::~Audio(){ //// DESTROY/ DEALLOCATE MEMORY

	al_destroy_sample(bMusic);
	al_destroy_sample(endGame);
	al_destroy_sample(caught);
	al_destroy_sample(respawn);
	al_destroy_sample(collect);

	al_destroy_sample_instance(MusicInstance);
};

void Audio::Init(){ //// RESERVE SOUNDS, SET MUSIC, INSTANCE

	al_reserve_samples(3); //// CAN PLAY 3 SOUNDS AT ONCE

	//// LOAD IN SOUNDS

	bMusic = al_load_sample("Sounds/background.ogg");
	endGame = al_load_sample("Sounds/endGame.ogg");

	caught = al_load_sample("Sounds/caught_01.ogg");
	respawn = al_load_sample("Sounds/respawn_01.ogg");
	collect = al_load_sample("Sounds/collect_01.ogg");

	//// SET UP INSTANCE
	MusicInstance = al_create_sample_instance(bMusic);
	al_set_sample_instance_playmode(MusicInstance, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(MusicInstance, 1.0f);
	al_attach_sample_instance_to_mixer(MusicInstance, al_get_default_mixer());
};

void Audio::PlayMusic(){ //// PLAY BACKGROUND MUSIC
	al_play_sample_instance(MusicInstance);
};

void Audio::StopMusic(){ //// STOP BACKGROUND MUSIC
	al_stop_sample_instance(MusicInstance);
};

void Audio::PlayCaught(){ //// PLAY SOUND EFFECTS
	al_play_sample(caught, 0.7f, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
};

void Audio::PlayRespawn(){
	al_play_sample(respawn, 2.0f, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
};

void Audio::PlayCollect(){
	al_play_sample(collect, 1.0f, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
};

void Audio::PlayEndGame(){ //// PLAYE END MUSIC
		al_play_sample(endGame, 1.0f, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
};

