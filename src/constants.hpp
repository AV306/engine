#pragma once

#include <cstdint>
#include "types.hpp"
// TODO: make data-driven

// RPG Maker VX Ace uses 32x32 tiles, and each tilemap is 8 tiles by 16 tiles
// 
const uint TILESET_TILE_SIZE_PIXELS = 32;

// These two multiplied together must be <= 255
const uint8_t TILESET_WIDTH_TILES = 8;
const uint8_t TILESET_HEIGHT_TILES = 16;

const uint SPRITE_ATLAS_SPRITE_SIZE_PIXELS = 64;
const uint SPRITE_ATLAS_WIDTH_SPRITES = 12;
const uint SPRITE_ATLAS_HEIGHT_SPRITES = 8;