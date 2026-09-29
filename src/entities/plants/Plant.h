#pragma once

#include <SFML/Graphics.hpp>
#include "PlantDef.h"


class Plant
{
    const PlantDef& m_def;
    sf::Sprite      m_sprite;
    float           m_life;
    int             m_value;
    EffectType      m_effect;

public:
    Plant(
            const PlantDef& def,
            const sf::Texture& texture,
            sf::Vector2f position);

    sf::FloatRect getBounds() const;
    sf::Vector2f getCenter() const;

    void takeDamage(int damage);
    void regenerate(int amount);

    void draw(sf::RenderWindow& w);

};
