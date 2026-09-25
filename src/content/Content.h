#pragma once

#include "nlohmann/json.hpp"
#include <player/PlayerDef.h>

struct Content
{
    PlayerDef player;
    std::unordered_map<std::string, sf::Texture> textures;

    void load(const std::string& folder);
};
