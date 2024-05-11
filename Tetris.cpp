#include<bits/stdc++.h>
#include "Tetris.h"

using namespace std;

/*
    0 1 2 3
    4 5 6 7
*/
// hinh dang block
const int Tetris::figures[7][4] =
{
        0,1,2,3,
        0,4,5,6,
        2,6,5,4,
        1,2,5,6,
        2,1,5,4,
        1,4,5,6,
        0,1,5,6,
};

void Tetris::loadintro()
{
    SDL_GetMouseState(&xpos, &ypos);
    SDL_RenderCopy(render, intro, NULL, NULL);
    SDL_Rect dst;
    dst.x = 253;
    dst.y= 50;
    dst.w= 94;
    dst.h=53;
    if( 253 <= xpos && xpos <= (94+253) && 50 <=ypos && ypos<= (50+53))
    {
        Sound.effectAudio("sound/Play.mp3");
        SDL_RenderCopy(render, play2, NULL, &dst);
    }
    else
        SDL_RenderCopy(render, play1, NULL, &dst);
    Sound.backgroundAudio("sound/Intro.ogg");
    SDL_RenderPresent(render);

}

bool Tetris::init(const char* title)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
        if(window != NULL)
        {
            render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(render != NULL)
            {
                SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
                int imgFlags = IMG_INIT_PNG;
                int initted = IMG_Init(imgFlags);
                if((initted & imgFlags) != imgFlags)
                    cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << endl;


                background = IMG_LoadTexture(render,"img/background.png" );
                blocks = IMG_LoadTexture(render, "img/blocks.png");
                intro = IMG_LoadTexture(render, "img/intro.png");
                play1 = IMG_LoadTexture(render, "img/play1.png");
                play2 = IMG_LoadTexture(render, "img/play2.png");
                if(TTF_Init() != 0)
                    cout << TTF_GetError();
                txb1.loadtext("UTM Cookies.ttf", 45);
                txb2.loadtext("UTM Cookies.ttf", 35);
                txb_gameover.loadtext("UTM Cookies.ttf", 60);

                txb_gameover.setcolor(0, 0, 0, 0);

                txb1.settext("SCORE", render);
                txb2.settext("0", render);
                txb_gameover.settext("Game over", render);

                nextTetrimino();

            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
    isintro = true;
    running = true;
    return true;
}

void Tetris::nextTetrimino()
{
    color = 1 + rand() % 7;
    int n =rand() % 7;
    for(int i=0;i<4;i++){
        items[i].x = figures[n][i] % 4;
        items[i].y = figures[n][i] / 4;
    }
}


void Tetris::handleEvennts()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if(running)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&xpos, &ypos);
                if( 253 <= xpos && xpos <= (94+253) && 50 <=ypos && ypos<= (50+53))
                {
                    setintro(false);
                    Mix_Music* music = Mix_LoadMUS("D:/Tetris_SDL2/sound/Background.ogg");
                    Mix_VolumeMusic(20);
                    Mix_PlayMusic(music, -1);
                    if(music == NULL)
                    {
                        std::cerr << "ALO 123456 file tertris.cpp" << std::endl;
                    }
                }
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    rotate = true;
                    Sound.effectAudio("sound/Move.mp3");
                    break;
                case SDLK_LEFT:
                    move = -1;
                    Sound.effectAudio("sound/Move.mp3");
                    break;
                case SDLK_RIGHT:
                    move = 1;
                    Sound.effectAudio("sound/Move.mp3");
                    break;
                case SDLK_SPACE:
                    ispaused = !ispaused;
                default:
                    break;
                }
            default:
                break;
            }
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_DOWN])
        delay = 20;
}

void Tetris::setPosRect(SDL_Rect& rect, int x, int y, int w, int h)
{
    rect = {x, y, w, h};
}

void Tetris::moveRectPos(SDL_Rect& rect, int x, int y)
{
    rect.x += x;
    rect.y += y;
}

bool Tetris::isvalid()
{
    for(int i=0;i<4;i++)
        if(items[i].x < 0 || items[i].x >=Cols || items[i].y >=Lines)  //va cham vs field
            return false;
        else
            if(field[items[i].y][items[i].x])  //va cham vs block
                return false;
    return true;
}

void Tetris::gameplay()
{
    // backup
    if(ispaused == true) return;
    for(int i=0;i<4;i++)
        backup[i] = items[i];  // save block khi va cham

    ////// move
        for(int i=0;i<4;i++)
        {
            items[i].x += move;
        }
        if(!isvalid())   // xu li va cham khi move
            for(int i=0;i<4;i++)
                items[i] = backup[i];

     //// rotate
    if(rotate)
    {
        Point p=items[2]; //// center of rotation
        for(int i=0; i<4; i++)
        {
            int x=items[i].y - p.y;
            int y=items[i].x - p.x;
            items[i].x = p.x - x;
            items[i].y = p.y + y;
        }
        if(!isvalid())  // xu ly va cham khi rotate
            for(int i=0;i<4;i++)
                items[i] = backup[i];
    }


    //// tick
    if(currentTime - startTime > delay)
    {
        for(int i=0;i<4;i++)
            backup[i]=items[i];
        for(int i=0;i<4;i++)
            items[i].y++;
        if(!isvalid())
        {
            for(int i=0;i<4;i++)
                field[backup[i].y][backup[i].x] = color;
            nextTetrimino();
        }
        startTime = currentTime;
    }

    //// check lines
    int k = Lines - 1;
    for(int i=k;i>0;i--)
    {
        int count = 0;
        for(int j=0;j<Cols;j++)
        {
            if(field[i][j])
                count++;
            field[k][j] = field[i][j];
        }
        if(count<Cols)
            k--;
        if(count == Cols)
        {
            Sound.effectAudio("sound/Lineclear.mp3");
            score += 10;
            string text = to_string(score);
            txb2.settext(text, render);
        }
    }
    move = 0;
    rotate = false;

    delay = 500;
}

void Tetris::gameOver()
{
    int game_over_count = 0;
    for(int i = 0; i < Lines; i++)
    {
        for(int j = 0; j < Cols; j++)
        {
            if(field[i][j] != 0)
            {
                game_over_count ++;
                break;
            }
        }
    }
    if(game_over_count == Lines)
    {
        running = false;
    }
}

void Tetris::endgame()
{
    SDL_RenderCopy(render, intro, NULL, NULL);
    txb_gameover.draw(render, 150, 50);
    SDL_RenderPresent(render);
}

void Tetris::updateRender()
{
    if(ispaused == true) return;
    SDL_RenderCopy(render, background, NULL, NULL);
    txb1.draw(render, 450, 300);
    txb2.draw(render, 450, 350);

    //va cham vs day ( luu hinh anh cuoi cung khi o day - bao gom ca mau sac)
    for(int i=0;i<Lines;i++)
        for(int j=0;j<Cols;j++)
            if(field[i][j])
                {
                    setPosRect(srcR, field[i][j] * BlockW);  // Giu nguyen mau cua block khi dang o day
                    setPosRect(destR, j * BlockW, i * BlockH);
                    moveRectPos(destR, BlockW, ScreenH - (Lines +1) * BlockH);
                    SDL_RenderCopy(render, blocks, &srcR, &destR);
                }

    //Tao block
    for(int i=0;i<4;i++)
    {
        setPosRect(srcR, color * BlockW);
        setPosRect(destR, items[i].x * BlockW, items[i].y * BlockH);
        moveRectPos(destR, BlockW, ScreenH - (Lines +1) * BlockH);
        SDL_RenderCopy(render, blocks, &srcR, &destR);
    }

    SDL_RenderPresent(render);

}

// chong tran bo nho
void Tetris::clean()
{
    SDL_DestroyTexture(blocks);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(render);
    IMG_Quit();
    SDL_Quit();
}
