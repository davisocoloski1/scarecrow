#include <SFML/Graphics.hpp>
#include "Plant.h"
#include "entities/plants/PlantDef.h"

Plant::Plant(
        const PlantDef& def,
        const sf::Texture& texture,
        const sf::Texture& health_bar,
        sf::Vector2f position)
    : m_def(def)
    , m_life(def.life)
    , m_max_life(def.life)
    , m_value(def.value)
    , m_effect(def.effect)
    , m_hitbox_offset(def.hitbox_offset)
    , m_hitbox_size(def.hitbox_size)
    , m_sprite(texture) 
    , m_health_bar(health_bar) {
       m_sprite.setTextureRect(sf::IntRect(
                   def.sprite_pos, def.sprite_size));

       m_sprite.setPosition(position);
    }

sf::FloatRect Plant::getBounds() const { return m_sprite.getGlobalBounds(); }
sf::Vector2f Plant::getCenter() const 
{
    return sf::Vector2f{
        getBounds().position.x + getBounds().size.x / 2.f,
        getBounds().position.y + getBounds().size.y / 2.f};
}

sf::FloatRect Plant::hitbox() const
{
    return { m_sprite.getPosition() + sf::Vector2f(m_hitbox_offset), sf::Vector2f(m_hitbox_size) };
}

void Plant::takeDamage(int damage) { m_life -= damage; }
void Plant::regenerate(int amount) { m_life += amount; }

void Plant::resolveHealthBar(EntHealthBar& hb) { hb.resolveHealthBar(m_life, m_max_life, m_health_bar); }

void Plant::drawHealthBar(sf::RenderWindow& w)
{
    auto lb = m_health_bar.getLocalBounds();
    auto b = hitbox();
    
    m_health_bar.setOrigin(sf::Vector2f{
            lb.position.x + lb.size.x / 2.f, lb.position.y + lb.size.y / 2.f});

    m_health_bar.setPosition(sf::Vector2f{
            getCenter().x, b.position.y - 4.f});

    w.draw(m_health_bar);
}
void Plant::drawHitbox(sf::RenderWindow& w, sf::FloatRect r)
{
    sf::RectangleShape shape(r.size);
    shape.setPosition(r.position);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(-1.f);
    w.draw(shape);
}
void Plant::draw(sf::RenderWindow& w) { w.draw(m_sprite); }
