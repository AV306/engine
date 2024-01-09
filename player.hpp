#pragma once

#include "utils.hpp"
#include "constants.hpp"
#include "defines.hpp"
#include "types.hpp"

#include <cstdint>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

namespace Engine
{
    struct Player extends public sf::Drawable, public sf::Transformable
    {
        Player( std::string spriteAtlasPath, uint8_t startingTileIndex )
        {
            // Load sprite atlas
            // TODO: Some characters' sprites stretch across more than one map
            loadTextureFileOrThrow( this->spriteAtlas, spriteAtlasPath );

            // Populate vertex array
            this->vertices.setPrimitiveType( sf::Quads );
            this->vertices.resize( 4 );

            uint8_t u = startingTileIndex % SPRITE_ATLAS_WIDTH_SPRITES, v = startingTileIndex / SPRITE_ATLAS_WIDTH_SPRITES;
            //std::cout << SPRITE_ATLAS_SPRITE_SIZE_PIXELS << '\n';
            //uint8_t u = 0, v = 0;

            // Top left
            this->vertices[0].position = sf::Vector2f{ 0, 0 };
            this->vertices[0].texCoords = sf::Vector2f{ u * SPRITE_ATLAS_SPRITE_SIZE_PIXELS, v * SPRITE_ATLAS_SPRITE_SIZE_PIXELS };

            // Top right
            this->vertices[1].position = sf::Vector2f{ SPRITE_ATLAS_SPRITE_SIZE_PIXELS, 0 };
            this->vertices[1].texCoords = sf::Vector2f{ (u+1) * SPRITE_ATLAS_SPRITE_SIZE_PIXELS, v * SPRITE_ATLAS_SPRITE_SIZE_PIXELS };

            // Bottom right
            this->vertices[2].position = sf::Vector2f{ SPRITE_ATLAS_SPRITE_SIZE_PIXELS, SPRITE_ATLAS_SPRITE_SIZE_PIXELS };
            this->vertices[2].texCoords = sf::Vector2f{ (u+1) * SPRITE_ATLAS_SPRITE_SIZE_PIXELS, (v+1) * SPRITE_ATLAS_SPRITE_SIZE_PIXELS };

            // Bottom left
            this->vertices[3].position = sf::Vector2f{ 0, SPRITE_ATLAS_SPRITE_SIZE_PIXELS };
            this->vertices[3].texCoords = sf::Vector2f{ u * SPRITE_ATLAS_SPRITE_SIZE_PIXELS, (v+1) * SPRITE_ATLAS_SPRITE_SIZE_PIXELS };
        }

        private:
            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
            {
                // apply the entity's transform -- combine it with the one that was passed by the caller
                states.transform *= this->getTransform(); // getTransform() is defined by sf::Transformable

                // apply the texture
                states.texture = &spriteAtlas;

                // you may also override states.shader or states.blendMode if you want

                // draw the vertex array
                target.draw( vertices, states );
            }

            sf::Texture spriteAtlas;
            sf::VertexArray vertices;
    };
}