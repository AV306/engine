#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "types.hpp"
#include "utils.hpp"

namespace Engine
{
    struct GameEngine
    {
        GameEngine( std::string windowTitle, uint width, uint height )
            : window{ sf::VideoMode{ width, height }, windowTitle }
        {
            std::cout << "Initialising window (" << width << ", " << height << ")\n";
        }

        void setGameLoop( std::function<void( float )> loopFunc )
        {
            this->gameLoop = loopFunc;
        }

        void run()
        {
            while ( this->window.isOpen() )
            {
                this->deltaTime = clock.restart().asSeconds();
                this->gameLoop( deltaTime );
            }
        }

        sf::RenderWindow& getWindow()
        {
            return this->window;
        }

        private:
            sf::RenderWindow window;
            std::function<void( float )> gameLoop;
            sf::Clock clock{};
            float deltaTime{};
    };
}