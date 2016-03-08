#pragma once
#include <allegro5/allegro_audio.h>	 //// AUDIO
#include <allegro5/allegro_acodec.h> //// CODEC AUDIO

class Audio
{
public:

	ALLEGRO_SAMPLE * bMusic;
	ALLEGRO_SAMPLE * endGame;
	ALLEGRO_SAMPLE * caught;
	ALLEGRO_SAMPLE * respawn;
	ALLEGRO_SAMPLE * collect;

	ALLEGRO_SAMPLE_INSTANCE * MusicInstance;

	Audio();
	~Audio();

	void Init();				//// RESERVE SOUNDS, SET MUSIC
	void PlayMusic();			//// PLAY BACKGROUND MUSIC
	void StopMusic();
	void PlayCaught();			//// PLAY SOUND EFFECTS
	void PlayRespawn();
	void PlayCollect();
	void PlayEndGame();			//// PLAY END MUSIC
};

