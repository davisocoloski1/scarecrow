#pragma once

#include <SFML/Graphics.hpp>
#include "effects/Effects.h"

enum class PlantType { Corn, Pumpkin, Tomato };

struct PlantDef
{
    std::string id;
    float life;
    int value;
    EffectType effect;
    std::string sprite;
    sf::Vector2i sprite_pos;
    sf::Vector2i sprite_size;
};
