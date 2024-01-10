#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cstdint>
#include <iostream>
#include <string>

#include "entity.hpp"
#include "utils.hpp"
#include "constants.hpp"
#include "defines.hpp"
#include "types.hpp"

namespace Engine
{
    struct Player extends public Entity
    {
        Player( sf::Texture* textureAtlasPointer, uint8_t startingTileIndex )
            : Entity{ textureAtlasPointer, startingTileIndex }
        {}

        virtual void update( float deltaTime ) override
        {
            xMovement = 0, yMovement = 0;

            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
                xMovement = 20.0 * deltaTime;
            else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
                xMovement = -20.0 * deltaTime;

            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
                yMovement = -20.0 * deltaTime;
            else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
                yMovement = 20.0 * deltaTime;

            this->move( xMovement, yMovement );
        }

        private:
            float xMovement{};
            float yMovement{};
    };
}