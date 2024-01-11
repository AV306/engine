#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>

#include "types.hpp"
#include "utils.hpp"

namespace Engine
{
    struct AnimationNode
    {
        AnimationNode( float frameDuration, std::initializer_list<sf::IntRect> frames )
        {
            this->frameDurationSeconds = frameDuration;
            this->frames{ frames };
        }

        sf::IntRect& getCurrentFrame()
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

            if ( this->time > this->frameDurationSeconds )
            {
                // If enough time has passed for at least one frame to pass,
                // calculate the number of frames that should have passed
                uint framesToAdvanceBy = (uint) (this->time / this->frameDurationSeconds);

                // Set the timer to the remaining amount of time
                this->time %= this->frameDurationSeconds;

                // Advance frame counter
                this->currentFrameIndex += framesToAdvanceBy;
            }
        }

        private:
            float frameDurationSeconds;
            std::vector<sf::IntRect> frames;
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