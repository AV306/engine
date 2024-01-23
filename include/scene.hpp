#pragma once

#include <SFML/Graphics.hpp>

using SceneFunction = std::function<void( sf::Event&, float )>;

namespace Engine
{
    /**
     * Interface representing a game scene, to be extended from.
     * Add fields for objects you need to be in scope (e.g. entities, maps, sprites) in subclasses.
     */
    struct Scene
    {
        virtual void operator()( sf::Event& event, float deltaTime ) = 0;
    };
}