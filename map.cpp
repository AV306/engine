#pragma once

#include <SFML/Graphics.hpp>

#include "types.hpp"

#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace Engine
{
    sf::Texture tilemap;

    void initTilemap( string tilemap_path )
    {
        if ( !tilemap.loadFromFile( tilemap_path ) )
            throw invalid_argument{ "Failed to load sprite atlas" };
    }

    struct Map
    {
        Map( string filename )
        {
            ifstream map_ifstream{ filename };

            // Ensure map file is valid
            char M, A, P;
            map_ifstream >> M >> A >> P;
            if ( !map_ifstream || M != 'M' || A != 'A' || P != 'P' ) throw invalid_argument{ "Invalid map file provided" };

            // Read width and height from map
            map_ifstream >> this->width >> this->height;

            // Allocate space for tile array
            
            this->tiles = new uchar[width*height];

            // Populate tile array
            for ( auto i = 0; i < width*height; i++ ) map_ifstream >> this->tiles[i];

            // Build texture
            this->build_texture();
        }

        Map( uchar width, uchar height, uchar* tiles ) : width{ width }, height{ height }
        {
            // Populate tile array
            this->tiles = std::move( tiles );

            // Build texture
            this->build_texture();
        }

        ~Map() noexcept
        {
            delete[] tiles;
            tiles = nullptr;
        }

        private:
            uchar width; // Width of map in tiles
            uchar height; // Height of map in tiles
            uchar* tiles; // Array of tilemap indexes

            sf::Texture texture; // Complete map texture

            //vector<ushort> border_tiles; // Array of tile array indexes that cannot be moved onto

            void build_texture()
            {
                this->texture.create( )
            }
    };
}