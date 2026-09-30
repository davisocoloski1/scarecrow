#include "Player.h"
#include "PlayerDef.h"
#include "player/health_bar.h"

#include <SFML/Graphics.hpp>

Player::Player(
        const PlayerDef& def,
        const sf::Texture& texture,
        const sf::Texture& health_bar_texture,
        sf::Vector2f position)
    : m_def(def)
    , m_life(def.life)
    , m_speed(def.speed)
    , m_damage(def.damage)
    , m_sprite(texture)
    , m_health_bar(health_bar_texture)
    , m_hitbox_offset(def.hitbox_offset)
    , m_hitbox_size(def.hitbox_size)
{
    m_sprite.setPosition(position);
    m_max_life = m_life;
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
sf::FloatRect Player::hitbox() const { return { m_sprite.getPosition() + sf::Vector2f(m_hitbox_offset), sf::Vector2f(m_hitbox_size) }; }
sf::Vector2f Player::getCenter() const
{
    return sf::Vector2f{
        getBounds().position.x + getBounds().size.x / 2.f,
        getBounds().position.y + getBounds().size.y / 2.f};
}

void Player::takeDamage(int damage) { m_life -= damage; }
void Player::heal(int amount) { m_life += amount; }

void Player::resolveHealthBar(HealthBar& hb)
{
    if (m_life <= 0) m_health_bar.setTextureRect(hb.frame8);
    else if (m_life <= m_max_life * .125) m_health_bar.setTextureRect(hb.frame7);
    else if (m_life <= m_max_life * .250) m_health_bar.setTextureRect(hb.frame6);
    else if (m_life <= m_max_life * .375) m_health_bar.setTextureRect(hb.frame5);
    else if (m_life <= m_max_life * .500) m_health_bar.setTextureRect(hb.frame4);
    else if (m_life <= m_max_life * .625) m_health_bar.setTextureRect(hb.frame3);
    else if (m_life <= m_max_life * .750) m_health_bar.setTextureRect(hb.frame2);
    else m_health_bar.setTextureRect(hb.frame1);
}

void Player::drawHitbox(sf::RenderWindow& w, sf::FloatRect r)
{
    sf::RectangleShape shape(r.size);
    shape.setPosition(r.position);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(-1.0);
    w.draw(shape);
}

void Player::drawHealthBar(sf::RenderWindow& w)
{
    auto lb = m_health_bar.getLocalBounds();

    m_health_bar.setOrigin(sf::Vector2f{
            lb.position.x + lb.size.x / 2.f, lb.position.y + lb.size.y / 2.f});

    auto b = getBounds();

    m_health_bar.setPosition(sf::Vector2f{
            getCenter().x, b.position.y - 4.f});

    w.draw(m_health_bar);
}
void Player::draw(sf::RenderWindow& w) { w.draw(m_sprite); }

