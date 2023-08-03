#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include<vector>
#include "Player.hpp"

using namespace std;

int main(int argc, char* argv[]){
    // if(SDL_Init(SDL_INIT_VIDEO) > 0 || !IMG_Init(IMG_INIT_PNG)){
    //     cout << "SDL Error, " << SDL_GetError() << endl;
    // }
    // else {
    //     cout << "SDL Works!";
    // }

    Render renderWindow("Game", 960, 672);

    SDL_Event event;

    std::vector<Entity> tileTextures;
    
    SDL_Texture *grassTexture = renderWindow.loadTexture("res/images/ground_grass_1.png");
    SDL_Texture *skyTexture = renderWindow.loadTexture("res/images/Sky.png");
    SDL_Texture *warrior = renderWindow.loadTexture("res/images/mage.png");

    Entity platform(96,96, grassTexture);
    Entity sky(96, 96, skyTexture);

    Entity character(475, 600-(96*2), warrior);
    // const int Xspeed = 10;
    // const int Yspeed
    const float gravity = 0.9;
    Player player(character);

    tileTextures.push_back(sky);
    tileTextures.push_back(platform);

    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;
    //float fps = 1 / 60;
    
    bool gameRunning = true;
    while (gameRunning){
        //Uint32 start = SDL_GetTicks();

        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
        lastTime = currentTime;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT){
                gameRunning = false;
            }
        }
            renderWindow.clear();
            player.moveCharacter(deltaTime);
            player.applyGravity(deltaTime);
            renderWindow.render(tileTextures, player, deltaTime);
            renderWindow.renderCharacter(player);

            // Uint32 end = SDL_GetTicks();
            // if(end - start < fps){
            //     while(end - start < fps){
            //     end = SDL_GetTicks();
            //     }
            // }

            renderWindow.display();
            
    }
    

    renderWindow.cleanUp();
    SDL_Quit();

    return 0;
}