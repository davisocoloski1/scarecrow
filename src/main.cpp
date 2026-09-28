#include "content/Content.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <random>

#include "entities/mob/Mob.h"
#include "player/Player.h"
#include "entities/plants/Plant.h"

#include "physics/physics.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 360}), "Scarecrow", sf::Style::None, sf::State::Windowed);
    window.setFramerateLimit(60);
    auto wb = window.getSize();

    sf::Texture bgTexture("assets/sprites/background.png");
    sf::Sprite background(bgTexture);

    std::mt19937 rng(std::random_device{}());

    Content content;
    content.load("./data");

    Player player(content.player, content.textures.at(content.player.sprite), {100.f, 100.f});

    sf::Texture plants_texture;
    if (!plants_texture.loadFromFile("assets/sprites/plants/plants.png")) return 1;
    std::vector<Plant> plants;
    int plant_amount = 0;
    sf::Clock plantClock;

    std::vector<Mob> mobs;
    int mob_amount = 0;
    sf::Clock mobClock;
    
    bool toggleHitboxes = false;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                if (key->scancode == sf::Keyboard::Scancode::F1) toggleHitboxes = !toggleHitboxes;
        }

        // Random position for plants spawn
        std::uniform_int_distribution<int> plantsPosX(
                32.f, wb.x - 32.f);
        std::uniform_int_distribution<int> plantsPosY(
                32.f, wb.y - 32.f);
        
        // Random position for mobs spawn
        std::uniform_int_distribution<int> mobsPosX(
                24.f, wb.x - 24.f);
        std::uniform_int_distribution<int> mobsPosY(
                24.f, wb.y - 24.f);

        std::uniform_real_distribution<float> plantProbability(0, 1);
        std::uniform_real_distribution<float> mobProbability(0, 1);
        std::string plantType = "";
        std::string mobType = "";
        if (plantClock.getElapsedTime().asSeconds() >= 2.0 && plant_amount <= 30)
        {
            float plantProb = plantProbability(rng);
            if (plantProb <= 1.0 && plantProb > 0.2)
                plantType = "corn";
            else if (plantProb <= 0.2 && plantProb > 0.05)
                plantType = "tomato";
            else 
                plantType = "pumpkin";

            PlantDef& def = content.plants.at(plantType);
            Plant p(def, content.textures.at(def.sprite), 
                    sf::Vector2f{(float)plantsPosX(rng), (float)plantsPosY(rng)});

            plantClock.restart();
            plants.push_back(p);
            plant_amount += 1;
        }

        if (mobClock.getElapsedTime().asSeconds() >= 3.5 && mob_amount <= 15)
        {
            float mobProb = mobProbability(rng);
            if (mobProb <= 1.0 && mobProb > 0.5)
                mobType = "rat";
            else if (mobProb <= 0.5 && mobProb > 0.25)
                mobType = "locust";
            else if (mobProb <= 0.25 && mobProb > 0.05)
                mobType = "mole";
            else
                mobType = "crow";

            MobDef& def = content.mobs.at(mobType);
            Mob m(def, content.textures.at(def.sprite),
                    sf::Vector2f{(float)mobsPosX(rng), (float)mobsPosY(rng)});

            mobClock.restart();
            mobs.push_back(m);
            mob_amount += 1;
        }

        for (Mob& m : mobs)
        {
            m.updateTarget(player, plants);
            m.chaseTarget();
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
        window.draw(background);

        player.draw(window);
        for (Plant& p : plants) p.draw(window);
        for (Mob& m : mobs) { 
            m.draw(window); 
            if (toggleHitboxes) m.drawHitbox(window, m.getGlobals()); 
        }

        window.display();
  }
}
