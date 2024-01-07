#include <SFML/Graphics.hpp>
#include <iostream>

#include "map.cpp"

using namespace std;

int main()
{
    sf::RenderWindow window{ sf::VideoMode{ 400, 300 }, "test" };
    

    // Load texture atlas
    Engine::initTilemap( "J:/silenced-engine/Assets/Graphics/Tilesets/00.png" );

    sf::Sprite sprite;
    sf::Texture spriteAtlas; spriteAtlas.loadFromFile( "J:/silenced-engine/Assets/Graphics/Characters/00.png" );
    sprite.setTexture( spriteAtlas );
    sprite.setTextureRect( sf::IntRect{ 0, 0, 64, 64 } );

    Engine::Map map{ "J:/silenced-engine/TestMap.map" };

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

        sprite.move( xMovement, yMovement );

        window.clear();
        window.draw( sprite );
        window.draw( map );
        window.display();
    }

    return 0;
}
