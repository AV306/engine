#include <SFML/Graphics.hpp>
#include <iostream>

#include "map.hpp"
#include "player.hpp"

#ifdef _WIN32
    #define PROJECT_DIR "J:/silenced-engine/"
#else
    #define PROJECT_DIR "/workspace/silenced-engine/"
#endif

using namespace std;

int main()
{
    sf::RenderWindow window{ sf::VideoMode{ 400, 300 }, "Silenced Engine" };

    Engine::Player player{ "/workspace/silenced-engine/Assets/Graphics/Characters/00.png", 1 };

    Engine::Map map{ "/workspace/silenced-engine/TestMap.map", "/workspace/silenced-engine/Assets/Graphics/Tilesets/00.png" };

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
