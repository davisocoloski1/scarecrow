#pragma once

#include "entities/mob/MobDef.h"
#include "entities/plants/PlantDef.h"
#include <player/PlayerDef.h>

struct Content
{
    PlayerDef player;
    std::unordered_map<std::string, PlantDef> plants;
    std::unordered_map<std::string, MobDef> mobs;
    std::unordered_map<std::string, sf::Texture> textures;

    void load(const std::string& folder);
};
