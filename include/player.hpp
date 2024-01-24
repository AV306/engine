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
        Player( sf::Texture& textureAtlas, uint8_t startingTileIndex )
            : Entity{ textureAtlas, startingTileIndex }
        {}

        Player( sf::Texture* textureAtlasPointer, uint8_t startingTileIndex )
            : Entity{ textureAtlasPointer, startingTileIndex }
        {}

        virtual void update( float deltaTime ) override
        {
            // Basic movement
            xMovement = 0; yMovement = 0;

            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
                xMovement -= speed;

            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
                xMovement += speed;

            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
                yMovement -= speed;

            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
                yMovement += speed;

            this->move( xMovement * deltaTime, yMovement * deltaTime );
        }

        private:
            float speed = 32;
            float xMovement{};
            float yMovement{};
    };
}