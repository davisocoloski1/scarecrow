#include "Mob.h"
#include "player/Player.h"
#include "entities/plants/Plant.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <limits>


Mob::Mob(MobDef& def, sf::Texture& texture, sf::Vector2f pos)
    : m_def(def)
    , m_life(def.life)
    , m_damage(def.damage)
    , m_attack_cooldown(def.attack_cooldown)
    , m_target(def.target)
    , m_speed(def.speed)
    , m_sprite(texture) 
    , m_hitbox_offset(def.hitbox_offset) 
    , m_hitbox_size(def.hitbox_size) {
        m_sprite.setTextureRect(sf::IntRect(
                    def.sprite_pos, def.sprite_size));
        m_sprite.setPosition(pos);
    }

sf::FloatRect Mob::getGlobals() const { return m_sprite.getGlobalBounds(); }
int Mob::getLife() const { return m_life; }
int Mob::getDamage() const { return m_damage; }
float Mob::getAttackCooldown() const { return m_attack_cooldown; }
sf::FloatRect Mob::hitbox() const 
{
    return {
        m_sprite.getPosition() + sf::Vector2f(m_hitbox_offset),
        sf::Vector2f(m_hitbox_size)};
}
sf::Vector2f Mob::getCenter() const 
{ 
    return sf::Vector2f{
        hitbox().position.x + hitbox().size.x / 2.f,
        hitbox().position.y + hitbox().size.y / 2.f};
}
Target Mob::getTarget() const { return m_target; }


void Mob::setPosition(sf::Vector2f pos) { m_sprite.setPosition(pos); }
void Mob::setAttackCooldown(float attack_cooldown) { m_attack_cooldown = attack_cooldown; }
void Mob::takeDamage(int damage) { m_life -= damage; }
void Mob::heal(int amount) { m_life += amount; }
void Mob::setDamage(int damage) { m_damage = damage; }

void Mob::updateTarget(Player& p, std::vector<Plant>& plants)
{
    m_target_position.reset();

    if (m_target == Target::None) return;

    const sf::Vector2f mobPos = getCenter();
    float shortestDist = std::numeric_limits<float>::max();

    if (m_target == Target::Player || m_target == Target::Closest)
    {
        m_target_position = p.getCenter();
        shortestDist = (p.getCenter() - mobPos).lengthSquared();
    }

    if (m_target == Target::Player) return;

    for (const Plant& plant : plants)
    {
        const sf::Vector2f plantPos = plant.getCenter();
        const float dist = (plantPos - mobPos).lengthSquared();

        if (dist < shortestDist)
        {
            shortestDist = dist;
            m_target_position = plantPos;
        }
    }
}

void Mob::chaseTarget()
{
    if (!m_target_position) return;

    const sf::Vector2f toTarget = *m_target_position - getCenter();

    if (toTarget.lengthSquared() <= m_speed * m_speed)
    {
        m_sprite.move(toTarget);
        return;
    }

    m_sprite.move(toTarget.normalized() * m_speed);
}

void Mob::drawHitbox(sf::RenderWindow& w, const sf::FloatRect r)
{
    sf::RectangleShape shape(r.size);
    shape.setPosition(r.position);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(-1.f);
    w.draw(shape);
}

void Mob::draw(sf::RenderWindow& w) { w.draw(m_sprite); }
