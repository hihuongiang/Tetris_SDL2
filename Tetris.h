#pragma once
#ifndef TETRIS_H_
#define TETRIS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "textbox.h"
#include "sound.h"

class Tetris{
public:
    Tetris()
    {

    }
    ~Tetris()
    {

    }

    void setCurrentTime(Uint32 t)
    {
        currentTime = t;
    }

    bool isrunning()
    {
        return running;
    }

    bool getintro()
    {
        return isintro;
    }

    void setintro(bool x)
    {
        isintro = x;
    }

    bool isvalid();
    bool init(const char* title);
    void loadintro();
    void nextTetrimino();
    void handleEvennts();
    void setPosRect(SDL_Rect& rect, int x = 0, int y = 0, int w = BlockW, int h = BlockH);
    void moveRectPos(SDL_Rect& rect, int x, int y);
    void gameplay();
    void gameOver();
    void endgame();
    void updateRender();
    void clean();
    bool getisWait()
    {
        return iswait;
    }

private:

    enum{ ScreenW = 600, ScreenH = 800};
    enum{ BlockW = 36, BlockH = 36 };
    enum{ Lines = 20, Cols = 10};

    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;
    SDL_Texture *background = NULL, *blocks = NULL, *intro = NULL,
                *play1 = NULL, *play2 = NULL;
    SDL_Rect srcR = {0, 0, BlockW, BlockH }, destR = { 0, 0, BlockW, BlockH };

    bool isintro = false;
    bool running = false;
    int field[Lines][Cols] = { {0} };
    static const int figures[7][4];
    struct Point
    {
        int x,y;
    }items[4], backup[4];
    textbox txb1, txb2, txb_gameover;
    sound Sound;
    int xpos,ypos;
    int color = 1;
    int move = 0;
    int score = 0;
    bool ispaused = false;
    bool iswait = true;
    bool rotate = false;
    unsigned int delay = 300;
    Uint32 startTime = 0, currentTime = 0;
};

#endif // TETRIS_H_
