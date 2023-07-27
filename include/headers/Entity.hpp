#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Entity{

    public:
        Entity(float x, float y, SDL_Texture *texture);
        Entity();
        float getX();
        float getY();
        SDL_Rect getCurrentFrame();
        void setCurrentFrameX(float x);
        void setCurrentFrameY(float y);
        SDL_Texture *getTexture();

    private:
        float x, y;
        SDL_Rect currentFrame;
        SDL_Texture *texture;
};