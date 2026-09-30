#pragma once

#include <SFML/Graphics.hpp>

struct EntHealthBar 
{
    sf::IntRect frame1 = sf::IntRect({0, 0}, {24, 5});
    sf::IntRect frame2 = sf::IntRect({0, 6}, {24, 5});
    sf::IntRect frame3 = sf::IntRect({0, 12}, {24, 5});
    sf::IntRect frame4 = sf::IntRect({0, 18}, {24, 5});
    sf::IntRect frame5 = sf::IntRect({0, 24}, {24, 5});
    sf::IntRect frame6 = sf::IntRect({0, 30}, {24, 5});
    sf::IntRect frame7 = sf::IntRect({0, 36}, {24, 5});
    sf::IntRect frame8 = sf::IntRect({0, 42}, {24, 5});

    
    void resolveHealthBar(int life, int max_life, sf::Sprite& health_bar)
    {
        if (life <= 0) health_bar.setTextureRect(sf::IntRect({0, 0}, {24, 0}));
        else if (life <= max_life * .125) health_bar.setTextureRect(frame8);
        else if (life <= max_life * .250) health_bar.setTextureRect(frame7);
        else if (life <= max_life * .375) health_bar.setTextureRect(frame6);
        else if (life <= max_life * .500) health_bar.setTextureRect(frame5);
        else if (life <= max_life * .625) health_bar.setTextureRect(frame4);
        else if (life <= max_life * .750) health_bar.setTextureRect(frame3);
        else if (life <= max_life * .875) health_bar.setTextureRect(frame2);
        else health_bar.setTextureRect(frame1);
    }

};
