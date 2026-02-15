#ifndef RETRO_DUNGEON_TYPES_HPP
#define RETRO_DUNGEON_TYPES_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <functional>

namespace retro_dungeon {

using EntityId = uint64_t;
using HealthPoints = int32_t;
using DamagePoints = int32_t;
using Position = std::pair<int, int>;

struct PositionHash {
    size_t operator()(const Position& pos) const {
        return std::hash<int>()(pos.first) ^ (std::hash<int>()(pos.second) << 1);
    }
};

enum class TileType {
    Floor,
    Wall,
    Door,
    StairsUp,
    StairsDown,
    Trap
};

enum class ItemType {
    Weapon,
    Armor,
    Potion,
    Gold,
    Food
};

enum class EnemyType {
    Goblin,
    Orc,
    Skeleton,
    Zombie,
    Dragon,
    Rat,
    Spider
};

enum class Direction {
    North,
    South,
    East,
    West
};

enum class GameState {
    MainMenu,
    Playing,
    Inventory,
    Paused,
    GameOver,
    Victory
};

constexpr Position INVALID_POSITION{-1, -1};
constexpr EntityId INVALID_ENTITY_ID = 0;
constexpr HealthPoints MAX_HEALTH = 100;
constexpr HealthPoints MIN_HEALTH = 0;

}

#endif