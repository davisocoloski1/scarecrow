#pragma once

#include <SFML/Graphics.hpp>
#include "PlantDef.h"
#include "entities/health_bar.h"


class Plant
{
    const PlantDef& m_def;
    sf::Sprite      m_sprite;
    sf::Sprite      m_health_bar;
    int             m_life;
    int             m_max_life;
    int             m_value;
    EffectType      m_effect;
    sf::Vector2i    m_hitbox_offset;
    sf::Vector2i    m_hitbox_size;

public:
    Plant(
            const PlantDef& def,
            const sf::Texture& texture,
            const sf::Texture& health_bar,
            sf::Vector2f position);

    sf::FloatRect getBounds() const;
    sf::Vector2f getCenter() const;
    sf::FloatRect hitbox() const;

    void takeDamage(int damage);
    void regenerate(int amount);

    void resolveHealthBar(EntHealthBar& hb);

    void drawHealthBar(sf::RenderWindow& w);
    void drawHitbox(sf::RenderWindow& w, sf::FloatRect r);
    void draw(sf::RenderWindow& w);

};
