#pragma once

#include <SFML/Graphics.hpp>
#include "PlayerDef.h"
#include "health_bar.h"

class Player
{
    const PlayerDef& m_def;
    int m_life;
    float m_speed;
    float m_damage;
    sf::Sprite m_sprite;
    sf::Sprite m_health_bar;
    sf::Vector2i m_hitbox_offset;
    sf::Vector2i m_hitbox_size;
    int m_max_life;

public:
    Player(
            const PlayerDef& def,
            const sf::Texture& texture,
            const sf::Texture& health_bar_texture,
            sf::Vector2f position);

    sf::FloatRect getBounds() const;
    sf::FloatRect hitbox() const;
    sf::Vector2f getCenter() const;

    void takeDamage(int damage);
    void heal(int amount);
    void resolveHealthBar(HealthBar& hb);

    void move(sf::Vector2f v, sf::Vector2u window_size);
    void drawHitbox(sf::RenderWindow& w, sf::FloatRect r);
    void drawHealthBar(sf::RenderWindow& w);
    void draw(sf::RenderWindow& w);
};
