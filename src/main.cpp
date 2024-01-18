#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "argspp.h"

#include "cache.hpp"
#include "map.hpp"
#include "engine.hpp"
#include "entity.hpp"
#include "gui.hpp"
#include "player.hpp"

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

    // Global stuff
    Engine::AssetCache<sf::Texture> tilesetTextureCache{ assetDirectoryPath / "Graphics/Tilesets/" };
    Engine::AssetCache<sf::Texture> spriteAtlasTextureCache{ assetDirectoryPath / "Graphics/Characters/" };
    Engine::AssetCache<sf::Font> fontCache{ assetDirectoryPath / "Fonts" };

    Engine::Player player{ spriteAtlasTextureCache.getAssetPointer( "00.png" ), 1 };
    Engine::Entity entity{ spriteAtlasTextureCache.getAssetPointer( "22.png" ), 2 };

    Engine::Map map{ "/workspace/silenced-engine/TestMap2.map", tilesetTextureCache.getAssetPointer( "00.png" ) };

    Engine::GuiCanvas canvas{};
    canvas.writeText( "Hi there!", fontCache.getAssetPointer( "VL-Gothic-Regular(FromThatSteamGuy).ttf" ), 30 );
    
    // Engine instance
    Engine::GameEngine engine{ "Engine", 400, 300 };
    engine.getWindow().setFramerateLimit( framerateLimit );


    auto loop = [ & ] ( float deltaTime )
    {
        // Events
        sf::Event event;
        while ( engine.getWindow().pollEvent( event ) )
            if ( event.type == sf::Event::Closed ) engine.getWindow().close();

        player.update( deltaTime );

        engine.getWindow().clear();
        engine.getWindow().draw( map );
        engine.getWindow().draw( entity );
        engine.getWindow().draw( player );
        engine.getWindow().draw( canvas );
        engine.getWindow().display();
    };

    engine.setGameLoop( loop );

    engine.run();

    return 0;
}
