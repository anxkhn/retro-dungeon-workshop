#include <catch2/catch_all.hpp>
#include "retro_dungeon/game.hpp"

TEST_CASE("Player initialization", "[player]") {
    retro_dungeon::Player player(1, "TestHero", {5, 5});
    
    REQUIRE(player.name == "TestHero");
    REQUIRE(player.health == 100);
    REQUIRE(player.maxHealth == 100);
    REQUIRE(player.level == 1);
    REQUIRE(player.isAlive());
}

TEST_CASE("Player movement", "[player]") {
    retro_dungeon::Player player(1, "Hero", {10, 10});
    
    SECTION("Move north") {
        player.move(retro_dungeon::Direction::North);
        REQUIRE(player.pos.second == 9);
    }
    
    SECTION("Move south") {
        player.move(retro_dungeon::Direction::South);
        REQUIRE(player.pos.second == 11);
    }
    
    SECTION("Move east - has bug") {
        player.move(retro_dungeon::Direction::East);
        REQUIRE(player.pos.first == 12);
    }
    
    SECTION("Move west") {
        player.move(retro_dungeon::Direction::West);
        REQUIRE(player.pos.first == 9);
    }
}

TEST_CASE("Player health management", "[player]") {
    retro_dungeon::Player player(1, "Hero", {5, 5});
    
    SECTION("Healing increases health") {
        player.health = 50;
        player.heal(20);
        REQUIRE(player.health == 70);
    }
    
    SECTION("Healing caps at max health") {
        player.health = 90;
        player.heal(50);
        REQUIRE(player.health == 100);
    }
    
    SECTION("Taking damage reduces health") {
        player.takeDamage(30);
        REQUIRE(player.health == 70);
    }
    
    SECTION("Health can go below zero - bug") {
        player.takeDamage(150);
        REQUIRE(player.health >= 0);
    }
}

TEST_CASE("Player inventory", "[player]") {
    retro_dungeon::Player player(1, "Hero", {5, 5});
    
    SECTION("Can add items") {
        auto item = std::make_shared<retro_dungeon::Item>("Sword", retro_dungeon::ItemType::Weapon, '/', 10, 5, 0);
        REQUIRE(player.addItem(item));
        REQUIRE(player.inventory.size() == 1);
    }
    
    SECTION("Inventory boundary - bug") {
        for (int i = 0; i < 25; ++i) {
            auto item = std::make_shared<retro_dungeon::Item>("Item" + std::to_string(i), retro_dungeon::ItemType::Potion, '!', 5, 0, 10);
            player.addItem(item);
        }
        REQUIRE(player.inventory.size() <= 20);
    }
}