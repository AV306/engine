#pragma once

#include "types.hpp"
#include <cstddef>
#include <exception>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace Engine
{
    struct Map
    {
        Map( string filename )
        {
            ifstream map_ifstream{ filename };

            // Ensure map file is valid
            char M, A, P;
            map_ifstream >> M >> A >> P;
            if ( M != 'M' || A != 'A' || P != 'P' ) throw invalid_argument{ "Invalid map file provided" };

            // Read width and height from map
            map_ifstream >> this->width >> this->height;

            // Allocate space for tile array
            
            this->tiles = new uchar[width*height];

            // Populate tile array
            for ( auto i = 0; i < width*height; i++ )
                map_ifstream >> this->tiles[i];
        }

        ~Map() noexcept
        {
            delete[] tiles;
            tiles = nullptr;
        }

        uchar width; // Width of map in tiles
        uchar height; // Height of map in tiles
        uchar* tiles; // Array of tilemap indexes
        //vector<ushort> border_tiles; // Array of tile array indexes that cannot be moved onto
    };
}