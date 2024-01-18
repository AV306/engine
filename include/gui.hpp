#pragma once

#include <SFML/Graphics.hpp>

#include <filesystem>

#include "defines.hpp"
#include "types.hpp"

namespace Engine
{
    struct GuiCanvas extends public sf::Drawable, sf::Transformable
    {
        GuiCanvas()
        {

        }

        void writeText( std::string text, sf::Font* fontPointer, uint size, sf::Text::Style style, sf::Vector2f position )
        {
            // Construct text object in vector
            sf::Text& textRef = this->texts.emplace_back( text, *fontPointer, size );

            // Update other properties not included in constructor
            textRef.setStyle( style );
            textRef.setPosition( position );
        }

        void writeText( std::string text, sf::Font* fontPointer, uint size )
        {
            // Construct text object in vector
            sf::Text& textRef = this->texts.emplace_back( text, *fontPointer, size );
        }

        std::vector<sf::Text>& getTexts()
        {
            return this->texts;
        }

        private:
            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
            {
                // apply the entity's transform -- combine it with the one that was passed by the caller
                states.transform *= this->getTransform(); // getTransform() is defined by sf::Transformable

                for ( auto& text : this->texts )
                    target.draw( text );
            }

            std::vector<sf::Text> texts;
    };
}