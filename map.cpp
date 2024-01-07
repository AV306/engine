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
            std::ifstream map_ifstream{ filename };

            // Ensure map file is valid
            char M, A, P;
            map_ifstream >> M >> A >> P;
            if ( !map_ifstream || M != 'M' || A != 'A' || P != 'P' ) throw std::invalid_argument{ "Invalid map file provided" };

            // Read width and height from map
            map_ifstream >> this->width >> this->height;

            // Allocate space for tile array
            // We have to use quads because the texcoords are discontinuous
            this->vertices.setPrimitiveType( sf::Quads );
            this->vertices.resize( width * height * 4 );

            // Populate VAO
            for ( uchar x = 0; x < width; x++ )
            {
                for ( uchar y = 0; y < height; y++ )
                {
                    // The index of the current map tile
                    uint map_tileIndex = x + (y * width);


                    // Seek to point in ifstream that defines the tile to use for this quad
                    // Add 5 to the tile index because of "MAP" header and the map dimensions
                    
                    map_ifstream.seekg( 5 + map_tileIndex, std::ios::beg );
                    uint tileset_tileIndex; map_ifstream >> tileset_tileIndex;
                    //std::cout << "Tileset tile index: " << tileset_tileIndex << '\n';
                    tileset_tileIndex = 2;

                    // Get the coordinates of the upper-right corner of the tile in the tileset
                    uint u = (tileset_tileIndex % TILESET_WIDTH_TILES) * TILESET_TILE_SIZE_PIXELS;
                    uint v = (tileset_tileIndex / TILESET_WIDTH_TILES) * TILESET_TILE_SIZE_PIXELS;

                    std::cout << "Tileset UV: " << u << ", " << v << '\n';

                    // Get pointer to the corner of the current map tile quad
                    sf::Vertex* quad = &(vertices[map_tileIndex * 4]);

                    // Define corners
                    quad[0].position = sf::Vector2f( x * TILESET_TILE_SIZE_PIXELS, y * TILESET_TILE_SIZE_PIXELS );
                    quad[1].position = sf::Vector2f( (x + 1) * TILESET_TILE_SIZE_PIXELS, y * TILESET_TILE_SIZE_PIXELS );
                    quad[2].position = sf::Vector2f( (x + 1) * TILESET_TILE_SIZE_PIXELS, (y + 1) * TILESET_TILE_SIZE_PIXELS );
                    quad[3].position = sf::Vector2f( x * TILESET_TILE_SIZE_PIXELS, (y + 1) * TILESET_TILE_SIZE_PIXELS );

                    // Define texcoords
                    quad[0].texCoords = sf::Vector2f( u * TILESET_TILE_SIZE_PIXELS, v * TILESET_TILE_SIZE_PIXELS );
                    quad[1].texCoords = sf::Vector2f( (u + 1) * TILESET_TILE_SIZE_PIXELS,v * TILESET_TILE_SIZE_PIXELS );
                    quad[2].texCoords = sf::Vector2f( (u + 1) * TILESET_TILE_SIZE_PIXELS, (v + 1) * TILESET_TILE_SIZE_PIXELS );
                    quad[3].texCoords = sf::Vector2f( u * TILESET_TILE_SIZE_PIXELS, (v + 1) * TILESET_TILE_SIZE_PIXELS );
                }
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