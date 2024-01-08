#pragma once

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "types.hpp"
#include "utils.hpp"

#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "defines.hpp"

namespace Engine
{
    //sf::Texture tileset;

    /*void initTilemap( std::string tileset_path )
    {
        if ( !tileset.loadFromFile( tileset_path ) )
            throw std::invalid_argument{ "Failed to load tileset atlas" };
    }*/



    struct Map extends public sf::Drawable, public sf::Transformable
    {
        Map( std::string& mapFilename, std::string& tilesetFilename )
        {
            // Initialise tileset texture
            loadTextureFileOrThrow( this->texture );
            std::ifstream mapStream{ mapFilename };

            // Ensure map file is valid
            char M, A, P;
            mapStream >> M >> A >> P;
            if ( !mapStream || M != 'M' || A != 'A' || P != 'P' )
                throw std::invalid_argument{ "Invalid map file provided" };

            // Read width and height from map
            mapStream >> this->width >> this->height;
            std::cout << "W: " << width << "; H: " << height << '\n';

            // Allocate space for tile array
            // We have to use quads because the texcoords are discontinuous
            this->vertices.setPrimitiveType( sf::Quads );
            this->vertices.resize( width * height * 4 );

            // Populate VAO
            // 0xFF * 0xFF = 0xFE01
            for ( ushort i = 0; i < width*height; i++ )
            {
                uchar tileID;
                mapStream >> tileID;
                //std::cout << (int) tileID;

                ushort x = i % width, y = i / width;
                uchar u = tileID % TILESET_WIDTH_TILES, v = tileID / TILESET_WIDTH_TILES;

                // Top-left corner
                this->vertices[i].position = sf::Vector2f{ x * TILESET_TILE_SIZE_PIXELS, y * TILESET_TILE_SIZE_PIXELS };
                this->vertices[i].texCoords = sf::Vector2f{ u * TILESET_TILE_SIZE_PIXELS, v * TILESET_HEIGHT_TILES };

                // Top-right
                this->vertices[i+1].position = sf::Vector2f{ (x+1) * TILESET_TILE_SIZE_PIXELS, y * TILESET_TILE_SIZE_PIXELS };
                this->vertices[i+1].texCoords = sf::Vector2f{ (u+1) * TILESET_TILE_SIZE_PIXELS, v * TILESET_HEIGHT_TILES };

                // Bottom right
                this->vertices[i+2].position = sf::Vector2f{ (x+1) * TILESET_TILE_SIZE_PIXELS, (y+1) * TILESET_TILE_SIZE_PIXELS };
                this->vertices[i+2].texCoords = sf::Vector2f{ (u+1) * TILESET_TILE_SIZE_PIXELS, (v+1) * TILESET_HEIGHT_TILES };

                // Bottom left
                this->vertices[i+3].position = sf::Vector2f{ x * TILESET_TILE_SIZE_PIXELS, y * TILESET_TILE_SIZE_PIXELS };
                this->vertices[i+3].texCoords = sf::Vector2f{ (u+1) * TILESET_TILE_SIZE_PIXELS, (v+1) * TILESET_HEIGHT_TILES };
            }
        }

        /*Map( uchar width, uchar height, uchar* tiles ) : width{ width }, height{ height }
        {
            // Populate tile array

            // Build texture
        }*/
        private:
            uchar width; // Width of map in tiles
            uchar height; // Height of map in tiles
            //uchar* tiles; // Array of tilemap indexes

            sf::Texture tileset;
            sf::VertexArray vertices;

            //vector<ushort> border_tiles; // Array of tile array indexes that cannot be moved onto

            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
            {
                // apply the entity's transform -- combine it with the one that was passed by the caller
                states.transform *= this->getTransform(); // getTransform() is defined by sf::Transformable

                // apply the texture
                states.texture = &tileset;

                // you may also override states.shader or states.blendMode if you want

                // draw the vertex array
                target.draw( vertices, states );
            }
    };
}