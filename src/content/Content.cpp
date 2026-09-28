#include "Content.h"

#include "entities/mob/MobDef.h"
#include "entities/plants/PlantDef.h"
#include "nlohmann/json.hpp"
#include "player/PlayerDef.h"
#include <fstream>
#include <stdexcept>

namespace nlohmann 
{
template<>
    struct adl_serializer<sf::Vector2i>
    {
        static void from_json(const json& j, sf::Vector2i& v)
        {
            v.x = j.at("x").get<int>();
            v.y = j.at("y").get<int>();
        }
    };
}

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

// PLANTS

static EffectType parseEffect(const json& j)
{
    if (j.is_null()) return EffectType::None;

    const std::string s = j.get<std::string>();
    if (s == "heal")    return EffectType::Heal;
    if (s == "poison")  return EffectType::Poison;

    throw std::runtime_error("unknown effect: " + s);
}

static PlantDef parsePlant(const json& j)
{
    PlantDef p;
    p.life          = j.at("life").get<int>();
    p.value         = j.at("value").get<int>();
    p.effect        = parseEffect(j.at("effect"));
    p.sprite        = j.at("sprite").get<std::string>();
    p.sprite_pos    = j.at("sprite_pos").get<sf::Vector2i>();
    p.sprite_size   = j.at("sprite_size").get<sf::Vector2i>();
    return p;
}


// MOBS

static Target parseTarget(const json& j)
{
    if (j.is_null()) return Target::None;

    const std::string s = j.get<std::string>();
    if (s == "player") return Target::Player;
    if (s == "plant") return Target::Plant;
    if (s == "closest") return Target::Closest;

    throw std::runtime_error("unknown target: " + s);
}

static MobDef parseMob(const json& j)
{
    MobDef m;
    m.life              = j.at("life").get<int>();
    m.damage            = j.at("damage").get<int>();
    m.attack_cooldown   = j.at("attack_cooldown").get<float>();
    m.target            = parseTarget(j.at("target"));
    m.speed             = j.at("speed").get<float>();
    m.sprite            = j.at("sprite").get<std::string>();
    m.sprite_pos        = j.at("sprite_pos").get<sf::Vector2i>();
    m.sprite_size       = j.at("sprite_size").get<sf::Vector2i>();
    m.hitbox_offset     = j.at("hitbox_offset").get<sf::Vector2i>();
    m.hitbox_size       = j.at("hitbox_size").get<sf::Vector2i>();
    return m;
};

void Content::load(const std::string& folder)
{
    const std::string path = folder + "/player.json";
    const std::string plantsPath = folder + "/plants.json";
    const std::string mobsPath = folder + "/mobs.json";
    try {
        player = parsePlayer(readJson(path));

        json plantsJson = readJson(plantsPath);
        for (const json& entry : plantsJson)
        {
            PlantDef def = parsePlant(entry);
            def.id = entry.at("id").get<std::string>();
            plants[def.id] = def;
        }

        json mobsJson = readJson(mobsPath);
        for (const json& entry : mobsJson)
        {
            MobDef def = parseMob(entry);
            def.id = entry.at("id").get<std::string>();
            mobs[def.id] = def;
        }

        for (const auto& [id, def] : plants)
            textures.try_emplace(def.sprite, def.sprite);

        for (const auto& [id, def] : mobs)
            textures.try_emplace(def.sprite, def.sprite);
    }
    catch (const json::exception& e)
    {
        throw std::runtime_error(path + ": " + e.what());
    }

    textures.emplace(player.sprite, sf::Texture(player.sprite));
}

