// River Raid 2018
// Made by Micha³ Berdzik, AGH, 2018 ©
//------------------------------------------------------------------

#include "Audio.h"

using namespace std;


Audio::Audio(char* path)
{
	p_path = path;
	SetUp();
	loadMusic();
}


Audio::~Audio(void)
{
}


void Audio::loadMusic()
{
	music = Mix_LoadMUS(p_path);
}



void Audio::playMusic()
{
	Mix_PlayMusic(music, 1);
}

void Audio::playMusicInf()
{
	Mix_PlayMusic(music, -1);
}


void Audio::stopMusic()
{
	Mix_PlayMusic(music, 0);
}

void Audio::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

bool Audio::IsPlaying()
{
	if(Mix_PlayingMusic()) return true;
	else return false;
}

void Audio::SetUp()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}
