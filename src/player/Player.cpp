#include "Player.h"
#include "PlayerDef.h"

#include <SFML/Graphics.hpp>

Player::Player(
        const PlayerDef& def,
        const sf::Texture& texture,
        sf::Vector2f position)
    : m_def(def)
    , m_life(def.life)
    , m_sprite(texture)
{
    m_sprite.setPosition(position);

}

void Player::move(sf::Vector2f v, sf::Vector2u window_size)
{
    if (v.x == 0.f && v.y == 0.f) return;
    m_sprite.move(v.normalized() * m_def.speed);

    auto b = m_sprite.getGlobalBounds();
    auto pos = m_sprite.getPosition();

    pos.x = std::clamp(pos.x, 10.f, window_size.x - b.size.x - 10.f);
    pos.y = std::clamp(pos.y, 10.f, window_size.y - b.size.y - 10.f);

    m_sprite.setPosition(pos);
}

sf::FloatRect Player::getBounds() const { return m_sprite.getGlobalBounds(); }
sf::Vector2f Player::getCenter() const
{
    return sf::Vector2f{
        getBounds().position.x + getBounds().size.x / 2.f,
        getBounds().position.y + getBounds().size.y / 2.f};
}

void Player::takeDamage(int damage) { m_life -= damage; }
void Player::heal(int amount) { m_life += amount; }

void Player::draw(sf::RenderWindow& w) { w.draw(m_sprite); }

