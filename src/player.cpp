#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include <iostream>


Player::Player(Entity &character)
    : entity(character) {
    keyboardState = SDL_GetKeyboardState(NULL);
    gravity = 0.08f;
    yVelocityDown = -7;
    isJumping = false;
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

void Player::moveCharacter(float deltatime){
    int currentX, currentY;

    if (keyboardState[SDL_SCANCODE_LEFT])
    {
        currentX = getEntity().getCurrentFrame().x;
        if (currentX < 0)
            currentX = 0;
        getEntity().setCurrentFrameX(currentX - Xspeed);
    }
    if (keyboardState[SDL_SCANCODE_RIGHT])
    {
        currentX = getEntity().getCurrentFrame().x;
        if (currentX > 960 - 96)
            currentX = 960 - 96;
       getEntity().setCurrentFrameX(currentX + Xspeed);
    }
    if (keyboardState[SDL_SCANCODE_SPACE] && !isJumping)
    {
     
            isJumping = true;
            yVelocityUp = 7;
            yVelocityDown = -7;
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
        
        if(yVelocityUp >= 0.3){
            yVelocityUp -= gravity;
            getEntity().setCurrentFrameY(currentY - yVelocityUp * gravity);
        }
        else {
            yVelocityDown += gravity;
            entity.setCurrentFrameY(currentY + yVelocityDown * gravity);
            std::cout << entity.getCurrentFrame().y << std::endl;
        }
    } 
    else if (!collided){
        std::cout << "falling not jumping" << std::endl;
        yVelocityDown += gravity;
        entity.setCurrentFrameY(entity.getCurrentFrame().y + yVelocityDown * gravity);
    }

    if (collided)
    {
        std::cout << "fell" << std::endl;
        isJumping = false;
        yVelocityUp = 7;
        yVelocityDown = -7;
        //collided = false;
    }
}

void Player::collide(SDL_Rect &obj){
    std::cout << entity.getCurrentFrame().y << std::endl;
    entity.setCurrentFrameY(obj.y - obj.h);
}
//  672
//  545
//  480
//  576
