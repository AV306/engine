#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>

#include "argspp.h"

#include "cache.hpp"
#include "map.hpp"
#include "engine.hpp"
#include "entity.hpp"
#include "gui.hpp"
#include "player.hpp"
#include "scenes.cpp"

using namespace std;

int main( int argc, char** argv )
{
    // Argument parsing
    args::ArgParser parser{};
    parser.helptext = "Usage: <executable name> [--asset-dir=\"...\"] [--framerate <number>] ...";
    parser.version = "0.1";

    parser.option( "asset-dir assetdir assets", "/workspace/silenced-engine/SilencedAssets/" );
    parser.option( "framerate", "30" );
    //parser.flag( "quiet q" );
    parser.parse( argc, argv );

    std::filesystem::path assetDirectoryPath{ parser.value( "asset-dir" ) };
    uint framerateLimit = stoi( parser.value( "framerate" ) );

    // Global stuff (independent of scene)
    Engine::AssetCache<sf::Texture> tilesetTextureCache{ assetDirectoryPath / "Graphics/Tilesets/", '_' };
    Engine::AssetCache<sf::Texture> imageTextureCache{ assetDirectoryPath / "Graphics/Titles1/", '_' };
    Engine::AssetCache<sf::Texture> spriteAtlasTextureCache{ assetDirectoryPath / "Graphics/Characters/", '_' };
    Engine::AssetCache<sf::Font> fontCache{ assetDirectoryPath / "Fonts" };

    //Engine::GuiCanvas canvas{};
    //canvas.addStaticText( "FPS: ", fontCache.getAsset( "VL-Gothic-Regular(FromThatSteamGuy).ttf" ), 30 );
    
    // Engine instance
    Engine::GameEngine engine{ "Engine", 544, 416 };
    engine.getWindow().setFramerateLimit( framerateLimit );

    //MainMenu menu{ engine, imageTextureCache.getAsset( "122.png" ) };
    Level scene{ engine, spriteAtlasTextureCache, tilesetTextureCache };
    MainMenu menu{ engine, imageTextureCache.getAsset( "00.png" ), &scene };

    
    //engine.getWindow().setFramerateLimit( framerateLimit );

    engine.setGameLoop( &menu );
    //engine.setGameLoop( scene );

    engine.run();
    return 0;
}
