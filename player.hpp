#pragma once

#include "utils.hpp"
#include "defines.hpp"
#include "types.hpp"

#include <SFML/Graphics.hpp>

namespace Engine
{
    struct Player extends public sf::Drawable
    {
        Player( sf::Sprite& sprite )
        {
            this->sprite = sprite;
        }

        private:
            sf::Sprite sprite;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
            {
                target.draw( this->sprite, )
            }
    }
}