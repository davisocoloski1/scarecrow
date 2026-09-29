#pragma once

#include <SFML/Graphics.hpp>
#include "PlayerDef.h"

class Player
{
    const PlayerDef& m_def;
    int m_life;
    sf::Sprite m_sprite;

public:
    Player(
            const PlayerDef& def,
            const sf::Texture& texture,
            sf::Vector2f position);

    sf::FloatRect getBounds() const;
    sf::Vector2f getCenter() const;

    void takeDamage(int damage);
    void heal(int amount);

    void move(sf::Vector2f v, sf::Vector2u window_size);
    void draw(sf::RenderWindow& w);
};
