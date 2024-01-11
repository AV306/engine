#include <SFML/Graphics.hpp>
#include <iostream>

#include "cache.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "player.hpp"

using namespace std;

int main()
{
    Engine::TextureCache tilesetTextureCache{ "/workspace/silenced-engine/Assets/Graphics/Tilesets/" };
    Engine::TextureCache spriteAtlasTextureCache{ "/workspace/silenced-engine/Assets/Graphics/Characters/" };

    sf::RenderWindow window{ sf::VideoMode{ 400, 300 }, "Silenced Engine" };

    Engine::Player player{ spriteAtlasTextureCache.getTexturePointer( "00.png" ), 1 };

    Engine::Entity entity{ spriteAtlasTextureCache.getTexturePointer( "22.png" ), 2 };

    Engine::Map map{ "/workspace/silenced-engine/TestMap2.map", tilesetTextureCache.getTexturePointer( "00.png" ) };

    float yMovement{};
    float xMovement{};

    sf::Clock clock{};
    float deltaTime;
    while ( window.isOpen() )
    {
        deltaTime = clock.restart().asSeconds();
        
        // Events
        sf::Event event;
        while ( window.pollEvent( event ) )
            if ( event.type == sf::Event::Closed ) window.close();

        player.update( deltaTime );

        window.clear();
        window.draw( map );
        window.draw( entity );
        window.draw( player );
        window.display();
    }

    return 0;
}
