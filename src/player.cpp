#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include <iostream>


Player::Player(Entity &character)
    : entity(character) {
    keyboardState = SDL_GetKeyboardState(NULL);
    gravity = 0.1f;
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
       yVelocityUp = 5;
       yVelocityDown = -5;

    //    currentY = getEntity().getCurrentFrame().y;
    //    if (currentY < 0)
    //         currentY = 0;
        // getEntity().setCurrentFrameY(currentY - Yspeed);
    }

    

}

void Player::applyGravity(float deltatime){

    if (isJumping)
    {
        float currentY = getEntity().getCurrentFrame().y;
        //    if (currentY < 0)
        //         currentY = 0;
        
        if(yVelocityUp >= 0.3){
            yVelocityUp -= gravity;
            getEntity().setCurrentFrameY(currentY - yVelocityUp);
            std::cout << (entity.getCurrentFrame().y + yVelocityUp * gravity) << std::endl;
        
        }
        else{
            yVelocityDown += gravity;
            entity.setCurrentFrameY(entity.getCurrentFrame().y + yVelocityDown * gravity);
            std::cout << (entity.getCurrentFrame().y + yVelocityDown * gravity) << std::endl;
        }
        //std::cout << entity.getCurrentFrame().y << " " << yVelocity<< " " << deltatime << std::endl;
    } 

    if (entity.getCurrentFrame().y >= (672 - (96 * 2)))
    {
        isJumping = false;
        yVelocityUp = 0;
        yVelocityDown = 0;
    }
}
