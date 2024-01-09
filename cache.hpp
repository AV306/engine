#pragma once

#include <SFML/Graphics.hpp>

#include <filesystem>
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
            std::filesystem::path path{ textureDir };

            for ( const auto& entry : std::filesystem::directory_iterator{ path } )
            {
                sf::Texture tex{};
                loadTextureFileOrThrow( tex, entry.path() );
                this->textures.insert( entry.filename(), tex );
            }
        }

        sf::Texture* getTexturePointer( std::string filename )
        {
            return &(this->texture.at( filename ));
        }
    };
}