#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>

#include <cstdint>

#include "types.hpp"
#include "utils.hpp"

namespace Engine
{
    struct Frame
    {
        Frame( uint8_t atlasTileIndex, float frameDurationSeconds )
        {
            this->frameDurationSeconds = frameDurationSeconds;

            this->textureRect = sf::IntRect{
                (startingTileIndex % SPRITE_ATLAS_WIDTH_SPRITES) * SPRITE_ATLAS_SPRITE_SIZE_PIXELS,
                (startingTileIndex / SPRITE_ATLAS_WIDTH_SPRITES) * SPRITE_ATLAS_SPRITE_SIZE_PIXELS,
                SPRITE_ATLAS_SPRITE_SIZE_PIXELS,
                SPRITE_ATLAS_SPRITE_SIZE_PIXELS
            };
        }

        float getDuration()
        {
            return this->frameDurationSeconds;
        }

        sf::IntRect& getTextureRect()
        {
            return this->textureRect;
        }

        private:
            float frameDurationSeconds;
            sf::IntRect textureRect;
    };

    struct AnimationNode
    {
        AnimationNode( float frameDuration, std::initializer_list<uint8_t> frames )
        {
            this->frameDurationSeconds = frameDuration;
        }

        Frame& getCurrentFrame()
        {
            return this->frames[currentFrameIndex];
        }

        void setFrame( uint frame )
        {
            this->currentFrameIndex = frame;
        }

        void reset()
        {
            this->currentFrameIndex = 0;
        }

        void tick( float deltaTime )
        {
            this->time += deltaTime;

            
            
        }

        private:
            std::vector<Frame> frames;
            uint currentFrameIndex{};
            float time{};
    };

    /*struct AnimationController
    {
        AnimationController()
        {

        }

        void addNode( std::string id, AnimationNode node )
        {
            this->nodes.insert( {id, node} );
        }

        AnimationNode& getCurrentNode()

        private:
            std::map<std::string, AnimationNode> nodes{};
    }*/
}