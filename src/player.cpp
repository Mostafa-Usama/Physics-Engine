#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include <iostream>


Player::Player(Entity &character)
    : entity(character) {
    keyboardState = SDL_GetKeyboardState(NULL);
    gravity = 2;
    yVelocityDown = 0;
    isJumping = false;
    isFacingRight = true;
    Xspeed = 1;
    
}
Entity& Player::getEntity(){
    return entity;
}
float Player::getXSpeed(){
    return Xspeed;
}

float Player::getYSpeed(){
    return Yspeed;
}
float Player::getGravity(){
    return gravity;
}
void Player::setCollided(bool x){
    collided = x;
}
bool Player::getCollided(){
    return collided;
}
bool Player::getFacing(){
    return isFacingRight;
}

void Player::moveCharacter(float deltatime){
    float currentX = entity.getCurrentFrame().x, currentY;

    if (keyboardState[SDL_SCANCODE_RIGHT])
    {
        if (currentX >= 960 - 96){
            currentX = 960 - 96;
        }

        entity.setCurrentFrameX(currentX + (Xspeed));
        // std::cout << "Right: " <<  deltatime << " " << Xspeed << std::endl;
        isFacingRight = true;
    }
    else if (keyboardState[SDL_SCANCODE_LEFT])
    {
        if (currentX <= 0){
            currentX = 0;
        }
        entity.setCurrentFrameX(currentX - (Xspeed * deltatime));
        // std::cout << "Left: " <<  deltatime << " " << Xspeed << std::endl;
        isFacingRight = false;
    }
    if (keyboardState[SDL_SCANCODE_SPACE] && !isJumping)
    {
     
            isJumping = true;
            yVelocityUp = 200;
            yVelocityDown = -150;
            collided = false;
    }

    
}

SDL_bool Player::isColliding(SDL_Rect &obj){
    
    SDL_Rect tmp2 = entity.getCurrentFrame();

    if (tmp2.x + tmp2.w >= obj.x &&
        obj.x + obj.w >= tmp2.x &&
        tmp2.y + tmp2.h >= obj.y &&
        obj.y + obj.h >= tmp2.y 
        )
       return SDL_TRUE;
    else
       return SDL_FALSE;
}


void Player::applyGravity(float deltatime){

    if (isJumping)
    {
        float currentY = getEntity().getCurrentFrame().y;
        //    if (currentY < 0)
        //         currentY = 0;
        
        if(yVelocityUp >= 2){
            yVelocityUp -= gravity;
            getEntity().setCurrentFrameY(currentY - yVelocityUp * gravity * deltatime);
        }
        else {
            yVelocityDown += gravity;
            entity.setCurrentFrameY(currentY + yVelocityDown * gravity* deltatime);
        }
    } 
    else if (!collided){
        yVelocityDown += gravity;
        entity.setCurrentFrameY(entity.getCurrentFrame().y + yVelocityDown * gravity * deltatime);
    }

    if (collided)
    {
        //std::cout << "fell" << std::endl;
        isJumping = false;
        yVelocityUp = 200;
        yVelocityDown = -150;
        //collided = false;
    }
}
void Player::fall(float deltatime){
    yVelocityDown += gravity;
    // std::cout << entity.getCurrentFrame().y << " " << yVelocityDown << " ";

    entity.setCurrentFrameY(entity.getCurrentFrame().y + (yVelocityDown * gravity * deltatime));
    std::cout << (yVelocityDown * gravity * deltatime) << std::endl;
}

void Player::collide(SDL_Rect &obj){
    
    if (obj.y >= entity.getCurrentFrame().y && 
        entity.getCurrentFrame().x + entity.getCurrentFrame().w >= obj.x){
        entity.setCurrentFrameY(obj.y - obj.h);
    }
    if (obj.y < entity.getCurrentFrame().y && 
        entity.getCurrentFrame().x + (entity.getCurrentFrame().w) >= obj.x){
        if (isFacingRight){
        entity.setCurrentFrameX(obj.x - entity.getCurrentFrame().w);
        }
        else{
        entity.setCurrentFrameX(obj.x + obj.w);
        }
    }
    // if (obj.y + obj.h < entity.getCurrentFrame().y &&
    //     entity.getCurrentFrame().x + entity.getCurrentFrame().w >= obj.x)
    // {
    //     entity.setCurrentFrameY(obj.y + obj.h);
    // }
}
//  672
//  545
//  480
//  576
