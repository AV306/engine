#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <fstream>

#include "constants.hpp"
//#include "datafiles.hpp"
#include "defines.hpp"
#include "types.hpp"

namespace Engine
{
    struct Entity extends public sf::Sprite
    {
        // Note: the type of startingTileIndex was changed from uint8_t
        // to remove the limitation on sprite atlas size
        // This one is simple because entities aren't data-driven yet
        Entity( sf::Texture* textureAtlasPointer, uint startingTileIndex )
            : sf::Sprite{ 
                *textureAtlasPointer, // sf::Sprite accepts a reference but i'm bad so i used a pointer
                sf::IntRect{
                    (startingTileIndex % SPRITE_ATLAS_WIDTH_SPRITES) * SPRITE_ATLAS_SPRITE_SIZE_PIXELS,
                    (startingTileIndex / SPRITE_ATLAS_WIDTH_SPRITES) * SPRITE_ATLAS_SPRITE_SIZE_PIXELS,
                    SPRITE_ATLAS_SPRITE_SIZE_PIXELS,
                    SPRITE_ATLAS_SPRITE_SIZE_PIXELS
                }
            }
        {
            
        }

        virtual void update( float deltaTime )
        {

        }
    };

    /*std::vector readEntityData( std::string path )
    {
        std::vector entities{};

        DataFile file{ path, "ENT" };

        std::ifstream& fileInputStream = file.getInputStream();

        fileInputStream.get()
    }*/
}