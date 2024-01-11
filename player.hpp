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
            counter += deltaTime;

            if ( counter % delay == 0 )
            {
                // Set target delta
                if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
                    targetYDelta = -this->movementDistance;
                else ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
                    targetYDelta = this->movementDistance;

                if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
                    targetXDelta = -this->movementDistance;
                else ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
                    targetXDelta = this->movementDistance;
            }

            
        }

        private:
            const uint delay = 1;
            const short movementDistance = 32;
            const float movementSpeed = 64;
            bool shouldMove = false;

            short targetXDelta{};
            short targetYDelta{};

            short currentXDelta{};
            short currentYDelta{};

            float counter{};
    };
}