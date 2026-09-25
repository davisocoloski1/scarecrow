#include "content/Content.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <stdexcept>

#include "player/Player.h"

int main()
{
  sf::RenderWindow window(sf::VideoMode({1280, 720}), "Scarecrow", sf::Style::None, sf::State::Windowed);
  window.setFramerateLimit(60);
  sf::Vector2u winBounds{600, 600};

  Content content;
  content.load("./data");

  Player player(content.player, content.textures.at(content.player.sprite), {100.f, 100.f});

  while (window.isOpen())
  {
    while (const auto event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>()) window.close();
    }

    auto w_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W);
    auto a_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
    auto s_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S);
    auto d_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);

    sf::Vector2f v{0.f, 0};
    if (w_pressed) v.y -= 1;
    if (s_pressed) v.y += 1;
    if (a_pressed) v.x -= 1;
    if (d_pressed) v.x += 1;
    player.move(v, window.getSize());

    window.clear(sf::Color::Black);

    player.draw(window);

    window.display();
  }
}
