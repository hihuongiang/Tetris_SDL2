#include "textbox.h"

void textbox::loadtext(string filepath, int size)
{
    font = TTF_OpenFont(filepath.c_str(), size);
}

void textbox::settext(string text, SDL_Renderer* render)
{
    if(text != this->text && text != "")
    {
        if(textTexture != NULL)
            SDL_DestroyTexture(textTexture);
        this->text = text;

        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
        textTexture = SDL_CreateTextureFromSurface(render, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(textTexture, NULL, NULL, &dst.w, &dst.h);
    }

}

void textbox::draw(SDL_Renderer* render, int x, int y)
{
    dst.x = x;
    dst.y = y;
    SDL_RenderCopy(render, textTexture, NULL, &dst);

}


