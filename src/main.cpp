#include <SFML/Graphics.hpp>
#include <iostream>

#include "argspp.h"

#include "cache.hpp"
#include "map.hpp"
#include "engine.hpp"
#include "entity.hpp"
#include "player.hpp"

using namespace std;

int main( int argc, char** argv )
{
    // Argument parsing
    args::ArgParser parser{};
    parser.helptext = "Usage: <executable name> --asset-dir=\"\" ...";
    parser.version = "0.1";
    parser.option( "asset-dir" );
    parser.flag( "quiet q" );
    parser.parse( argc, argv );
    std::filesystem::path assetDirectoryPath{ parser.value( "asset-dir" ) };

    // Global stuff
    Engine::TextureCache tilesetTextureCache{ assetDirectoryPath / "Graphics/Tilesets/" };
    Engine::TextureCache spriteAtlasTextureCache{ assetDirectoryPath / "Graphics/Characters/", '!' };

    Engine::Player player{ spriteAtlasTextureCache.getTexturePointer( "00.png" ), 1 };
    Engine::Entity entity{ spriteAtlasTextureCache.getTexturePointer( "22.png" ), 2 };

    Engine::Map map{ "/workspace/silenced-engine/TestMap2.map", tilesetTextureCache.getTexturePointer( "00.png" ) };
    
    // Engine instance
    Engine::GameEngine engine{ "Engine", 400, 300 };


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
        engine.getWindow().display();
    };

    engine.setGameLoop( loop );

    engine.run();

    return 0;
}
