#pragma once

#include <SFML/Graphics.hpp>
#include "PlayerDef.h"

class Player
{
    const PlayerDef& m_def;
    float m_life;
    sf::Sprite m_sprite;

public:
    Player(
            const PlayerDef& def,
            const sf::Texture& texture,
            sf::Vector2f position);

    void move(sf::Vector2f v, sf::Vector2u window_size);
    void draw(sf::RenderWindow& w);
};
