#include <SFML/Graphics.hpp>
#include <iostream>

#include "cache.hpp"
#include "map.hpp"
#include "player.hpp"

using namespace std;

int main()
{
    Engine::TextureCache tilesetTextureCache{ "/workspace/silenced-engine/Assets/Graphics/Tilesets/" };

    sf::RenderWindow window{ sf::VideoMode{ 400, 300 }, "Silenced Engine" };

    Engine::Player player{ "/workspace/silenced-engine/Assets/Graphics/Characters/00.png", 1 };

    Engine::Map map{ "/workspace/silenced-engine/TestMap.map", tilesetTextureCache.getTexturePointer( "00.png" ) };

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
  
        // Inputs
        // FIXME: this is like the worst possible input system
        xMovement = 0, yMovement = 0;
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
            xMovement = 20.0 * deltaTime;
        else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
            xMovement = -20.0 * deltaTime;

        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
            yMovement = -20.0 * deltaTime;
        else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
            yMovement = 20.0 * deltaTime;

        player.move( xMovement, yMovement );

        window.clear();
        window.draw( map );
        window.draw( player );
        window.display();
    }

    return 0;
}
