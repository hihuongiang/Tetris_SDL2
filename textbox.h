#pragma once
#include<string>
#include<SDL.h>
#include<SDL_ttf.h>
using namespace std;

class textbox
{
private:
    TTF_Font* font;
    string text;
    SDL_Texture* textTexture = NULL;
    SDL_Rect dst;
    SDL_Color color {255, 255, 255, 0};

public:
    void loadtext(string filepath, int size);
    void settext(string text, SDL_Renderer* render);
    void setcolor(int r, int g, int b, int a)
    {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }
    void draw(SDL_Renderer* render, int x, int y);
};

