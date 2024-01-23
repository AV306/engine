#pragma once

#include <iostream>
#include "defines.hpp"
#include "engine.hpp"
#include "cache.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "scene.hpp"
using namespace std;

struct MainMenu extends public Engine::Scene
{
    MainMenu( Engine::GameEngine& engine, sf::Texture& backgroundImage, Engine::Scene* next )
        : engine{ engine },
        background{ backgroundImage },
        nextScene{ next }
    {

    }

    virtual void operator()( sf::Event& event, float deltaTime ) override
    {
        //if ( event.type == sf::Event::Closed ) engine.getWindow().close();

        engine.getWindow().clear();
        engine.getWindow().draw( this->background );
        engine.getWindow().display();

        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Enter ) )
            engine.setGameLoop( nextScene );
    }

    private:
        Engine::GameEngine& engine;
        sf::Sprite background;
        Engine::Scene* nextScene;
};

struct Level extends public Engine::Scene
{
    Level( Engine::GameEngine& engine, Engine::AssetCache<sf::Texture>& spriteAtlasTextureCache, Engine::AssetCache<sf::Texture>& tilesetTextureCache )
        : engine{ engine },
        spriteAtlasTextureCache{ spriteAtlasTextureCache },
        tilesetTextureCache{ tilesetTextureCache },
        entity{ spriteAtlasTextureCache.getAsset( "22.png" ), 8 },
        player{ spriteAtlasTextureCache.getAsset( "00.png" ), 4 },
        map{ "/workspace/silenced-engine/TestMap2.map", tilesetTextureCache.getAsset( "00.png" ) }
    {

    }

    virtual void operator()( sf::Event& event, float deltaTime ) override
    {
        // Events
        //if ( event.type == sf::Event::Closed ) engine.getWindow().close();

        //cout << "In level loop\n";

        // Updates
        player.update( deltaTime );

        // Rendering
        engine.getWindow().clear();
        engine.getWindow().draw( map );
        engine.getWindow().draw( entity );
        engine.getWindow().draw( player );
        engine.getWindow().display();
    }

    private:
        Engine::GameEngine& engine;
        Engine::AssetCache<sf::Texture>& spriteAtlasTextureCache;
        Engine::AssetCache<sf::Texture>& tilesetTextureCache;

        Engine::Entity entity;
        Engine::Player player;
        Engine::Map map;
};