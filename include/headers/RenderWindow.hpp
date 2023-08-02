#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include "Player.hpp"
#include <vector>

class Render{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
    public:
        Render(const char* title, int width, int height);
        SDL_Texture *loadTexture(const char* filePath);
        void clear();
        void render(std::vector <Entity> entity, Player& player, float deltatime);
        void renderCharacter(Player &entity);
        SDL_Renderer *getRenderer();
        // void characterMove(Entity &entity);
        void display();
        void cleanUp();
};