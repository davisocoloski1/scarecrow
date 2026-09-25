#include "Content.h"

#include "nlohmann/json.hpp"
#include "player/PlayerDef.h"
#include <fstream>
#include <stdexcept>

using nlohmann::json;

static json readJson(const std::string& path)
{
    std::ifstream in(path);
    if (!in) throw std::runtime_error("could not open " + path);

    try { return json::parse(in); }
    catch (const json::parse_error& e)
    {
        throw std::runtime_error(path + ": invalid JSON: " + e.what());
    }
}

static PlayerDef parsePlayer(const json& j)
{
    PlayerDef p;
    p.life      = j.at("life").get<int>();
    p.damage    = j.at("damage").get<float>();
    p.speed     = j.at("speed").get<float>();
    p.sprite    = j.at("sprite").get<std::string>();
    return p;
}

template <typename Def, typename ParseFn>
static void loadCategory(const std::string& path, std::unordered_map<std::string, Def>& out, ParseFn parse)
{
    json root = readJson(path);
    for (const auto& entry : root.items())
    {
        try
        {
            out[entry.key()] = parse(entry.key(), entry.value());
        }
        catch(const json::exception& e)
        {
            throw std::runtime_error(path + ", \"" + entry.key() + "\": " + e.what());
        }
    }
}

void Content::load(const std::string& folder)
{
    const std::string path = folder + "/player.json";
    try {
        player = parsePlayer(readJson(path));
    }
    catch (const json::exception& e)
    {
        throw std::runtime_error(path + ": " + e.what());
    }

    textures.emplace(player.sprite, sf::Texture(player.sprite));
}

