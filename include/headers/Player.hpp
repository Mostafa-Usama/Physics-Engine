#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
class Player{

    public:
        Player(Entity &character);
        Entity& getEntity();
        float getXSpeed();
        float getYSpeed();
        float getGravity();
        void moveCharacter(float deltatime);
        void applyGravity(float deltatime);
        

    private:
        Entity &entity;
        float Xspeed = 1;
        float Yspeed = 10;
        float gravity;
        float yVelocityUp;
        float yVelocityDown; // Vertical velocity
        bool isJumping;
        const Uint8 *keyboardState;
};