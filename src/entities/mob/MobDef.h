#pragma once

#include <SFML/Graphics.hpp>

enum class Target { Player, Plant, Closest, None };

struct MobDef
{
    std::string id;
    int life;
    int damage;
    float attack_cooldown;
    Target target;
    float speed;
    std::string sprite;
    sf::Vector2i sprite_pos;
    sf::Vector2i sprite_size;
    sf::Vector2i hitbox_offset;
    sf::Vector2i hitbox_size;
};
