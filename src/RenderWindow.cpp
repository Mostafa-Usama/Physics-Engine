#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.hpp"
#include <iostream>
#include "Entity.hpp"
#include <vector>
#include "Player.hpp"

Render::Render(const char* title, int width, int height):window(NULL), renderer(NULL){
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL){
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);

}

SDL_Renderer* Render:: getRenderer(){
    return renderer;
}

SDL_Texture* Render::loadTexture(const char* texture){
    SDL_Texture *text = IMG_LoadTexture(renderer, texture);
    return text;
}

void Render::clear(){
    SDL_RenderClear(renderer);
} 
void Render::render(std::vector <Entity>entity, Player& player ){
    // SDL_Rect src;
    // src.x = entity.getCurrentFrame().x;
    // src.y = entity.getCurrentFrame().y;
    // src.w = entity.getCurrentFrame().w;
    // src.h = entity.getCurrentFrame().h;

    // SDL_Rect dst;
    int width = entity[0].getCurrentFrame().w * 3;
    int height = entity[0].getCurrentFrame().h * 3;

    const int rows = 672 / height;
    const int cols = 960 / width;
    int tileMapData[rows][cols] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            int tileType = tileMapData[row][col];
            if (tileType >= 0 && tileType < entity.size())
            {
                SDL_Rect destRect = {col * width, row * height, width, height};
                SDL_RenderCopy(renderer, entity[tileType].getTexture(), NULL, &destRect);
                if(player.isColliding(destRect) && tileType == 1){
                    std::cout << "Collision detected ground" << std::endl;
                    player.setCollided(true);
                    player.collide(destRect);
                }
            //     else {
            //         player.setCollided(false);
            //    //     std::cout << "Collision detected sky" << std::endl;
            //     }
                // else if (player.isColliding(destRect) && tileType == 1)
                // {
                //     player.setCollided(false);
                // }
            }
           
        }
    }
}

void Render::renderCharacter(Player &entity){
    int width = entity.getEntity().getCurrentFrame().w * 3;
    int height = entity.getEntity().getCurrentFrame().h * 3;
    int x = entity.getEntity().getCurrentFrame().x;
    int y = entity.getEntity().getCurrentFrame().y;
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopy(renderer, entity.getEntity().getTexture(), NULL, &destRect);
}

// void Render::characterMove(Entity &entity){
//     SDL_Event event;
//     int speed = 10;
//     int currentX;
   
//         if(event.type == SDL_KEYDOWN){
//             switch(event.key.keysym.sym){
//                 case SDLK_RIGHT:
//                     currentX = entity.getCurrentFrame().x;
//                     entity.setCurrentFrameX(currentX + speed);
//                     break;

//                 case SDLK_LEFT:
//                     currentX = entity.getCurrentFrame().x;
//                     entity.setCurrentFrameX(currentX - speed);
//                     break;
                
            
//         }
//     }
// }


void Render::display(){
    SDL_RenderPresent(renderer);
}

void Render::cleanUp(){
    SDL_DestroyWindow(window);
}