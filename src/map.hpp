#pragma once

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "types.hpp"
#include "utils.hpp"

#include <cstddef>
#include <cstdint> // uint8_t and the like
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "defines.hpp"

namespace Engine
{
    struct Map extends public sf::Drawable, public sf::Transformable
    {
        Map( std::string mapFilename, sf::Texture* texturePointer )
        {
            std::cout << "Loading map " << mapFilename << '\n';

            // Set pointer to tileset texture
            this->tilesetTexturePointer = texturePointer;

            // Prepare to read map file
            std::ifstream mapStream{ mapFilename };

            // Ensure map file is valid: check header and streambits
            char M, A, P;
            mapStream >> M >> A >> P;
            if ( !mapStream || M != 'M' || A != 'A' || P != 'P' )
                throw std::invalid_argument{ "Invalid map file provided" };

            // Read width and height from map
            mapStream >> this->width >> this->height;
            std::cout << "Map is " << (short) this->width << " by " << (short) this->height << " tiles\n";

            // Allocate space for tile array
            // We have to use quads because the texcoords are discontinuous
            this->vertices.setPrimitiveType( sf::Quads );
            this->vertices.resize( width * height * 4 );


            // Populate VAO
            // 0xFF * 0xFF = 0xFE01
            for ( uint16_t mapTileIndex = 0; mapTileIndex < width*height; mapTileIndex++ )
            {
                // FIXME: Change this part to increase the tileset maximum size
                // You'll probably need to change this quite a bit,
                // I'll leave that to someone more experienced
                uint8_t tileID = (uint8_t) mapStream.get();
                //std::cout << "Drawing tile ID " << (short) tileID << "; ";

                uint16_t x = mapTileIndex % width, y = mapTileIndex / width;
                uint8_t u = tileID % TILESET_WIDTH_TILES, v = tileID / TILESET_WIDTH_TILES;

                uint startingVertexIndex = mapTileIndex * 4;

                // Top-left corner
                this->vertices[startingVertexIndex].position = sf::Vector2f{ x * TILESET_TILE_SIZE_PIXELS, y * TILESET_TILE_SIZE_PIXELS };
                this->vertices[startingVertexIndex].texCoords = sf::Vector2f{ u * TILESET_TILE_SIZE_PIXELS, v * TILESET_TILE_SIZE_PIXELS };

                // Top-right
                this->vertices[startingVertexIndex+1].position = sf::Vector2f{ (x+1) * TILESET_TILE_SIZE_PIXELS, y * TILESET_TILE_SIZE_PIXELS };
                this->vertices[startingVertexIndex+1].texCoords = sf::Vector2f{ (u+1) * TILESET_TILE_SIZE_PIXELS, v * TILESET_TILE_SIZE_PIXELS };

                // Bottom right
                this->vertices[startingVertexIndex+2].position = sf::Vector2f{ (x+1) * TILESET_TILE_SIZE_PIXELS, (y+1) * TILESET_TILE_SIZE_PIXELS };
                this->vertices[startingVertexIndex+2].texCoords = sf::Vector2f{ (u+1) * TILESET_TILE_SIZE_PIXELS, (v+1) * TILESET_TILE_SIZE_PIXELS };

                // Bottom left
                this->vertices[startingVertexIndex+3].position = sf::Vector2f{ x * TILESET_TILE_SIZE_PIXELS, (y+1) * TILESET_TILE_SIZE_PIXELS };
                this->vertices[startingVertexIndex+3].texCoords = sf::Vector2f{ u * TILESET_TILE_SIZE_PIXELS, (v+1) * TILESET_TILE_SIZE_PIXELS };
            }

            //std::cout << std::endl;
        }

        private:
            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
            {
                // apply the entity's transform -- combine it with the one that was passed by the caller
                states.transform *= this->getTransform(); // getTransform() is defined by sf::Transformable

                // apply the texture
                states.texture = tilesetTexturePointer;

                // you may also override states.shader or states.blendMode if you want

                // draw the vertex array
                target.draw( vertices, states );
            }

            
            uint8_t width; // Width of map in tiles
            uint8_t height; // Height of map in tiles
            //uint8_t* tiles; // Array of tilemap indexes

            sf::Texture* tilesetTexturePointer;
            sf::VertexArray vertices;

            //vector<uint16_t> border_tiles; // Array of tile array indexes that cannot be moved onto
    };
}