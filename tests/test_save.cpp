#include <catch2/catch_all.hpp>
#include "retro_dungeon/game.hpp"
#include <fstream>
#include <cstdio>

TEST_CASE("Save/Load roundtrip", "[save]") {
    retro_dungeon::Game game;
    game.initialize();
    game.newGame("TestHero");
    game.getPlayer()->health = 75;
    game.getPlayer()->gold = 50;
    game.getPlayer()->level = 3;
    
    const char* filename = "test_save.sav";
    
    SECTION("Save and load") {
        REQUIRE(game.saveGame(filename));
        REQUIRE(game.loadGame(filename));
        
        REQUIRE(game.getPlayer()->name == "TestHero");
        REQUIRE(game.getPlayer()->health == 75);
        REQUIRE(game.getPlayer()->gold == 50);
        REQUIRE(game.getPlayer()->level == 3);
    }
    
    std::remove(filename);
}

TEST_CASE("Save file format", "[save]") {
    retro_dungeon::Game game;
    game.initialize();
    game.newGame("Hero");
    
    const char* filename = "format_test.sav";
    game.saveGame(filename);
    
    SECTION("File contains correct field name - spelling bug") {
        std::ifstream file(filename);
        std::string line;
        std::getline(file, line);
        REQUIRE(line == "Hero");
        
        std::string values;
        std::getline(file, values);
        REQUIRE(values.find("defence") == std::string::npos);
    }
    
    std::remove(filename);
}

TEST_CASE("Load non-existent file", "[save]") {
    retro_dungeon::Game game;
    game.initialize();
    
    REQUIRE(!game.loadGame("nonexistent.sav"));
}