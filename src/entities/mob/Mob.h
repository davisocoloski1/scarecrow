#pragma once

#include <SFML/Graphics.hpp>
#include "MobDef.h"
#include "player/Player.h"
#include "entities/plants/Plant.h"

#include <optional>


class Mob
{
    const MobDef&                   m_def;
    sf::Sprite                      m_sprite;
    int                             m_life;
    int                             m_damage;
    float                           m_attack_cooldown;
    Target                          m_target;
    float                           m_speed;
    sf::Vector2i                    m_hitbox_offset;
    sf::Vector2i                    m_hitbox_size;
    std::optional<sf::Vector2f>     m_target_position;

public:
    Mob(MobDef& def, sf::Texture& texture, sf::Vector2f pos);

    sf::FloatRect getGlobals() const;
    int getLife() const;
    int getDamage() const;
    float getAttackCooldown() const;
    sf::FloatRect hitbox() const;
    sf::Vector2f getCenter() const;
    Target getTarget() const;

    void setPosition(sf::Vector2f pos);
    void takeDamage(int damage);
    void heal(int amount);
    void setAttackCooldown(float attack_cooldown);
    void setDamage(int damage);

    void updateTarget(Player& p, std::vector<Plant>& plants);
    void chaseTarget();
    
    void drawHitbox(sf::RenderWindow& w, const sf::FloatRect r);
    void draw(sf::RenderWindow& w);
};
