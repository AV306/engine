#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window{ sf::VideoMode{ 200, 200 }, "Test" };
    //sf::CircleShape shape{ 100.f };
    //shape.setFillColor( sf::Color::Green );

    // Load texture atlas
    sf::Texture spriteAtlas;
    if ( !spriteAtlas.loadFromFile(
        "J:/silenced-engine/Assets/Graphics/Characters/00.png"
    ) ) cout << "Failed to load sprite atlas\n";

    sf::Sprite sprite;
    sprite.setTexture( spriteAtlas );
    sprite.setTextureRect( sf::IntRect{ 0, 0, 64, 64 } );

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
            yMovement = 20.0 * deltaTime;
        else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
            yMovement = -20.0 * deltaTime;

        sprite.move( sf::Vector2f{ xMovement, yMovement } );

        window.clear();
        window.draw( sprite );
        window.display();
    }

    return 0;
}
