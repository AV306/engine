#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

#include "types.hpp"
#include "scene.hpp"
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

        void setGameLoop( Scene* loopFunc )
        {
            std::cout << "Changed game loop\n";
            this->gameLoop = loopFunc;
        }

        void run()
        {
            while ( this->window.isOpen() )
            {
                this->deltaTime = clock.restart().asSeconds();

                this->window.pollEvent( this->event );

                if ( event.type == sf::Event::Closed ) this->window.close();

                (*(this->gameLoop))( this->event, this->deltaTime );
            }
        }

        sf::RenderWindow& getWindow()
        {
            return this->window;
        }

        private:
            sf::RenderWindow window;
            sf::Event event;
            Scene* gameLoop;
            sf::Clock clock{};
            float deltaTime{};
    };
}