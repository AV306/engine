#pragma once

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <iostream>
#include <map>
#include <string>

#include "utils.hpp"

namespace Engine
{
    // TODO: template-ify
    struct TextureCache
    {
        TextureCache( std::string textureDir )
        {
            std::cout << "Caching textures from " << textureDir << '\n';
            std::filesystem::path path{ textureDir };

            for ( const auto& entry : std::filesystem::directory_iterator{ path } )
            {
                sf::Texture tex{};
                loadTextureFileOrThrow( tex, entry.path() );
                this->textures.insert( {entry.path().filename().string(), tex} );
            }
        }

        sf::Texture* getTexturePointer( std::string filename )
        {
            return &(this->textures.at( filename ));
        }

        private:
            std::map<std::string, sf::Texture> textures{};
    };
}