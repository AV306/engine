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
    template <typename T>
    struct AssetCache
    {
        // Constructor to load everything in one go
        AssetCache( std::filesystem::path assetDir )
            : assetDirectoryPath{ assetDir }
        {
            std::cout << "Caching assets from " << assetDir << '\n';

            for ( const auto& entry : std::filesystem::directory_iterator{ assetDir } )
                this->_loadAssetIntoMap( entry );
        }

        // Constructor to load only priority files and lazily load everything else
        AssetCache( std::filesystem::path assetDir, char priorityPrefix )
            : assetDirectoryPath{ assetDir }
        {
            std::cout << "Caching priority assets from " << assetDir << '\n';

            for ( const auto& entry : std::filesystem::directory_iterator{ assetDir } )
            {
                // Skip non-priority files
                if ( entry.path().filename().c_str()[0] != priorityPrefix ) continue;

                // Load priority file
                this->_loadAssetIntoMap( entry );
            }
        }

        T* getAssetPointer( std::string filename )
        {
            try
            {
                // Attempt to grab the texture with the filename and return a pointer to it
                // Will throw out_of_range if it's not present
                return &(this->assets.at( filename ));
            }
            catch ( const std::out_of_range& noSuchElementException )
            {
                // Texture not found, might not be loaded yet
                // Try loading it

                // Reconstruct the path
                std::filesystem::path filePath = this->assetDirectoryPath / filename;
                
                try
                {
                    std::cout << "(Lazy)";
                    this->_loadAssetIntoMap( filePath );
                }
                catch ( const std::invalid_argument& noSuchFileException )
                {
                    // Failed loading, file really isn't present
                    std::cout << "Failed to load asset from " << filename << '\n';
                    return nullptr;
                }
            }

            return &(this->assets.at( filename ));
        }

        private:
            void _loadAssetIntoMap( std::filesystem::path path )
            {
                std::cout << '\t';
                this->assets.emplace(
                    path.filename(),
                    loadAssetFileOrThrow<T>( path )
                );
            }

            const std::filesystem::path assetDirectoryPath;
            std::map<std::string, T> assets{};
    };
}