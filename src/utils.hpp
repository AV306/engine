#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

namespace Engine
{
    void loadTextureFileOrThrow( sf::Texture& tex, std::string filename )
    {
       if ( !tex.loadFromFile( filename ) )
            throw std::invalid_argument{ "Failed to load texture from " + filename };

        std::cout << "Loaded texture from " << filename << '\n';
    }

    sf::Texture loadTextureFileOrThrow( std::string filename )
    {
        sf::Texture tex{};
        if ( !tex.loadFromFile( filename ) )
            throw std::invalid_argument{ "Failed to load texture from " + filename };

        std::cout << "Loaded texture from " << filename << '\n';

        return tex; 
    }
}