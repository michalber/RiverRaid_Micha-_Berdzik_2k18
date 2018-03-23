// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#pragma once

#include "SDL_mixer.h"
#include <string>

class Audio
{
public:
	Audio(char*);
	~Audio(void);

	void loadMusic();

	void playMusic();
	void playMusicInf();
	void stopMusic();
	void SetMusicVolume(int);
	bool IsPlaying();

private:
	Mix_Music *music = NULL;
	const char* p_path=NULL;
	void SetUp();

};