#pragma once

#include <cstdint>
#include <exception>
#include <string>
#include "types.hpp"
// TODO: make data-driven

namespace Engine
{
    // RPG Maker VX Ace uses 32x32 tiles, and each tilemap is 8 tiles by 16 tiles
    // 
    uint TILESET_TILE_SIZE_PIXELS = 32;

    // These two multiplied together must be <= 255
    uint8_t TILESET_WIDTH_TILES = 8;
    const uint8_t TILESET_HEIGHT_TILES = 16;

    uint SPRITE_ATLAS_SPRITE_SIZE_PIXELS = 64;
    uint SPRITE_ATLAS_WIDTH_SPRITES = 12;
    uint SPRITE_ATLAS_HEIGHT_SPRITES = 8;

    /*void readConstants( std::string filename )
    {
        std::ifstream constantsFileInputStream{ filename };

        if ( !constantsFileInputStream ) throw std::invalid_argument{ "Invalid property file " + filename };


        while ( filename)
    }*/
}