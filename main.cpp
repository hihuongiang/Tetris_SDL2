#include "Tetris.h"
#include <bits/stdc++.h>

using namespace std;
int main(int argc, char* argv[]){
    srand(time(0));
    Tetris* tetris = new Tetris();
    const char* title = "Tetris";
    tetris->init(title);
    while(tetris->getisWait())
    {
        while (tetris->isrunning())
        {
            tetris->setCurrentTime(SDL_GetTicks());
            tetris->handleEvennts();
            if(tetris->getintro() == true)
            {
                tetris->loadintro();
            }
            else
            {
                tetris->gameplay();
                tetris->updateRender();
            }
            tetris->gameOver();
        }
        tetris->endgame();
        SDL_Event e;
        if(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                break;
            }

        }
    }
    tetris->clean();
    return 0;
}
