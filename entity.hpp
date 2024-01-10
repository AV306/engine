#pragma once

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "defines.hpp"

namespace Engine
{
    struct Entity extends public sf::Sprite
    {
        Entity( sf::Texture* textureAtlasPointer, uint8_t startingTileIndex )
            : sf::Sprite{ 
                *textureAtlasPointer, // sf::Sprite accepts a reference but i'm bad so i used a pointer
                sf::IntRect{
                    startingTileIndex % SPRITE_ATLAS_WIDTH_SPRITES,startingTileIndex / SPRITE_ATLAS_WIDTH_SPRITES,
                    SPRITE_ATLAS_SPRITE_SIZE_PIXELS,SPRITE_ATLAS_SPRITE_SIZE_PIXELS
                }
            }
        {
            
        }

        virtual void update( float deltaTime )
        {

        }
    };
}