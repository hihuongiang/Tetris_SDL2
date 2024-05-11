#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
using namespace std;

class sound
{
private:

public:
    void backgroundAudio(const char* nameSong);
    void effectAudio(const char* nameSong);
};
