#include "sound.h"
#include<bits/stdc++.h>

void sound::backgroundAudio(const char* nameSong)
{
    Mix_Music* music = NULL;
 	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout<< Mix_GetError();
	}
	music = Mix_LoadMUS(nameSong);
	if (music == NULL)
	{
		cout<< Mix_GetError();
	}
	if (!Mix_PlayingMusic())
        Mix_PlayMusic(music, -1);
}

void sound::effectAudio(const char* nameSong)
{
    Mix_Chunk* chunk = NULL;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout<< Mix_GetError();
	}
	chunk = Mix_LoadWAV(nameSong);
	if (chunk == NULL)
	{
		cout<< Mix_GetError();
	}
	if (!Mix_Playing(-1))
        Mix_PlayChannel(-1, chunk, 0);
}
