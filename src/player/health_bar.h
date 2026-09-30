#pragma once

#include <SFML/Graphics.hpp>

struct HealthBar
{
    sf::Texture health_bar;
    sf::IntRect frame1 = sf::IntRect({0, 0}, {24, 6});
    sf::IntRect frame2 = sf::IntRect({0, 7}, {24, 6});
    sf::IntRect frame3 = sf::IntRect({0, 14}, {24, 6});
    sf::IntRect frame4 = sf::IntRect({0, 21}, {24, 6});
    sf::IntRect frame5 = sf::IntRect({0, 28}, {24, 6});
    sf::IntRect frame6 = sf::IntRect({0, 35}, {24, 6});
    sf::IntRect frame7 = sf::IntRect({0, 42}, {24, 6});
    sf::IntRect frame8 = sf::IntRect({0, 49}, {24, 6});
};
