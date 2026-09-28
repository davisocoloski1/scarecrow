#include <SFML/Graphics.hpp>
#include "Plant.h"
#include "entities/plants/PlantDef.h"

Plant::Plant(
        const PlantDef& def,
        const sf::Texture& texture,
        sf::Vector2f position)
    : m_def(def)
    , m_life(def.life)
    , m_value(def.value)
    , m_effect(def.effect)
    , m_sprite(texture) {
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


void Plant::draw(sf::RenderWindow& w) { w.draw(m_sprite); }
