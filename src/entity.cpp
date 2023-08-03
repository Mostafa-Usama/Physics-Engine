#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(float x, float y, SDL_Texture *texture):x(x), y(y), texture(texture){

    currentFrame.x = x;
    currentFrame.y = y;
    currentFrame.w = 96;
    currentFrame.h = 96;
}
Entity::Entity(){

}
float Entity::getX(){
    return x;
}
float Entity::getY(){
    return y;
}
SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}
SDL_Texture* Entity::getTexture(){
    return texture;
}
void Entity::setCurrentFrameX(float x){
    currentFrame.x = x;
}

void Entity::setCurrentFrameY(float y)
{
    currentFrame.y = y;
}
