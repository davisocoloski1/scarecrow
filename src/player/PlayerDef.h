#pragma once

#include <SFML/Graphics.hpp>


struct PlayerDef
{
    std::string id;
    float speed;
    int damage, life;
    std::string sprite;
};
