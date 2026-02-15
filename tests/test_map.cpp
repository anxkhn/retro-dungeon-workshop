#include <catch2/catch_all.hpp>
#include "retro_dungeon/game.hpp"

TEST_CASE("Map creation", "[map]") {
    retro_dungeon::Map map(60, 20);
    
    REQUIRE(map.getWidth() == 60);
    REQUIRE(map.getHeight() == 20);
}

TEST_CASE("Map tile operations", "[map]") {
    retro_dungeon::Map map(60, 20);
    
    SECTION("Default tiles are walls") {
        REQUIRE(map.getTile(0, 0).type == retro_dungeon::TileType::Wall);
    }
    
    SECTION("Set floor tile") {
        map.setTile(10, 10, retro_dungeon::TileType::Floor);
        REQUIRE(map.getTile(10, 10).type == retro_dungeon::TileType::Floor);
        REQUIRE(map.getTile(10, 10).walkable);
    }
    
    SECTION("Get tile out of bounds - bug") {
        REQUIRE_THROWS_AS(map.getTile(-1, -1), std::out_of_range);
    }
}

TEST_CASE("Map walkability", "[map]") {
    retro_dungeon::Map map(60, 20);
    
    SECTION("Walls are not walkable") {
        REQUIRE(!map.isWalkable(0, 0));
    }
    
    SECTION("Floors are walkable") {
        map.setTile(10, 10, retro_dungeon::TileType::Floor);
        REQUIRE(map.isWalkable(10, 10));
    }
    
    SECTION("Out of bounds is not walkable") {
        REQUIRE(!map.isWalkable(-1, 0));
        REQUIRE(!map.isWalkable(100, 0));
    }
}

TEST_CASE("Map clear", "[map]") {
    retro_dungeon::Map map(60, 20);
    map.setTile(10, 10, retro_dungeon::TileType::Floor);
    
    map.clear();
    
    REQUIRE(map.getTile(10, 10).type == retro_dungeon::TileType::Wall);
}