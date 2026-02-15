#include <catch2/catch_all.hpp>
#include "retro_dungeon/game.hpp"

TEST_CASE("Random integer generation", "[random]") {
    retro_dungeon::DungeonGenerator gen;
    auto map = gen.generate(60, 20);
    
    REQUIRE(map != nullptr);
    REQUIRE(map->getWidth() == 60);
    REQUIRE(map->getHeight() == 20);
}

TEST_CASE("Dungeon generation", "[random]") {
    retro_dungeon::DungeonGenerator gen(42);
    
    auto map1 = gen.generate(60, 20);
    auto map2 = gen.generate(60, 20);
    
    SECTION("Maps have stairs") {
        REQUIRE(map1->getStairsDown() != retro_dungeon::INVALID_POSITION);
        REQUIRE(map2->getStairsDown() != retro_dungeon::INVALID_POSITION);
    }
}

TEST_CASE("Seeded generation is reproducible", "[random]") {
    retro_dungeon::DungeonGenerator gen1(12345);
    retro_dungeon::DungeonGenerator gen2(12345);
    
    auto map1 = gen1.generate(60, 20);
    auto map2 = gen2.generate(60, 20);
    
    REQUIRE(map1->getStairsDown() == map2->getStairsDown());
}