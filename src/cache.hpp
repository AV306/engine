#pragma once

#include <SFML/Graphics.hpp>

#include <exception>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>

#include "utils.hpp"

namespace Engine
{
    // TODO: template-ify
    // TODO: Lazy laoding
    struct TextureCache
    {
        // Constructor to load everything in one go
        TextureCache( std::string textureDir )
            : textureDirectoryPath{ textureDir }
        {
            std::cout << "Caching textures from " << textureDir << '\n';
            std::filesystem::path path{ textureDir };

            for ( const auto& entry : std::filesystem::directory_iterator{ path } )
                this->_loadTextureIntoMap( entry );
        }

        // Constructor to load only priority files and lazily load everything else
        TextureCache( std::string textureDir, char priorityPrefix )
            : textureDirectoryPath{ textureDir }
        {
            std::cout << "Caching priority textures from " << textureDir << '\n';
            std::filesystem::path path{ textureDir };

            for ( const auto& entry : std::filesystem::directory_iterator{ path } )
            {
                // Skip non-priority files
                if ( entry.path().filename().c_str()[0] != priorityPrefix ) continue;

                // Load priority file
                this->_loadTextureIntoMap( entry );
            }
        }

        sf::Texture* getTexturePointer( std::string filename )
        {
            try
            {
                // Attempt to grab the texture with the filename and return a pointer to it
                // Will throw out_of_range if it's not present
                return &(this->textures.at( filename ));
            }
            catch ( const std::out_of_range& noSuchElementException )
            {
                // Texture not found, might not be loaded yet
                // Try loading it

                // Reconstruct the path
                std::filesystem::path filePath = this->textureDirectoryPath / filename;
                
                try
                {
                    std::cout << "(Lazy)";
                    this->_loadTextureIntoMap( filePath );
                }
                catch ( const std::invalid_argument& noSuchFileException )
                {
                    // Failed loading, file really isn't present
                    std::cout << "Failed to load texture from " << filename << '\n';
                    return nullptr;
                }
            }

            return &(this->textures.at( filename ));
        }

        private:
            void _loadTextureIntoMap( std::filesystem::path path )
            {
                std::cout << '\t';
                this->textures.emplace(
                    path.filename(),
                    loadTextureFileOrThrow( path )
                );
            }

            const std::filesystem::path textureDirectoryPath;
            std::map<std::string, sf::Texture> textures{};
    };
}