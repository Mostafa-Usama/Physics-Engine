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
        void setCollided(bool x);
        bool getCollided();
        void moveCharacter(float deltatime);
        void applyGravity(float deltatime);
        SDL_bool isColliding(SDL_Rect &obj);
        void collide(SDL_Rect &obj);

    private:
        Entity &entity;
        float Xspeed = 1;
        float Yspeed = 10;
        float gravity;
        float yVelocityUp;
        float yVelocityDown; // Vertical velocity
        bool isJumping;
        bool collided = false;
        const Uint8 *keyboardState;
};