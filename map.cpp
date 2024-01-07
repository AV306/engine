#pragma once

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "types.hpp"

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
    sf::Texture tileset;

    void initTilemap( std::string tileset_path )
    {
        if ( !tileset.loadFromFile( tileset_path ) )
            throw std::invalid_argument{ "Failed to load tileset atlas" };
    }



    struct Map extends public sf::Drawable, public sf::Transformable
    {
        Map( std::string filename )
        {
            std::ifstream mapStream{ filename };

            // Ensure map file is valid
            char M, A, P;
            mapStream >> M >> A >> P;
            if ( !mapStream || M != 'M' || A != 'A' || P != 'P' )
                throw std::invalid_argument{ "Invalid map file provided" };

            // Read width and height from map
            mapStream >> this->width >> this->height;

            // Allocate space for tile array
            // We have to use quads because the texcoords are discontinuous
            this->vertices.setPrimitiveType( sf::Quads );
            this->vertices.resize( width * height * 4 );

            // Populate VAO
            for ( auto i = 0; i < width*height; i++ )
            {
                uchar tileID;
                mapStream >> tileID;
                std::cout << tileID;

                // Corners, starting from top-left, clockwise
                auto x = i % width, y = i / width;
                auto u = tileID % TILESET_WIDTH_TILES, v = tileID / TILESET_WIDTH_TILES;

                this->vertices[v].position = sf::Vector2f{ x * TILESET_TILE_SIZE_PIXELS, y * TILESET_TILE_SIZE_PIXELS };
                this->vertices[i].texCoords = sf::Vector2f{ u * TILESET_TILE_SIZE_PIXELS, v * TILESET_HEIGHT_TILES };
            }
        }

        /*Map( uchar width, uchar height, uchar* tiles ) : width{ width }, height{ height }
        {
            // Populate tile array

            // Build texture
        }*/

        ~Map() noexcept
        {
        }

        private:
            uchar width; // Width of map in tiles
            uchar height; // Height of map in tiles
            //uchar* tiles; // Array of tilemap indexes

            //sf::Texture texture;
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