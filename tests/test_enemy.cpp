#include <catch2/catch_all.hpp>
#include "retro_dungeon/game.hpp"

TEST_CASE("Enemy initialization", "[enemy]") {
    retro_dungeon::Enemy enemy(1, retro_dungeon::EnemyType::Goblin, {5, 5});
    
    REQUIRE(enemy.name == "Goblin");
    REQUIRE(enemy.symbol == 'g');
    REQUIRE(enemy.health == 20);
    REQUIRE(enemy.isAlive());
}

TEST_CASE("Enemy types", "[enemy]") {
    SECTION("Goblin stats") {
        retro_dungeon::Enemy goblin(1, retro_dungeon::EnemyType::Goblin, {0, 0});
        REQUIRE(goblin.health == 20);
        REQUIRE(goblin.attackPower == 5);
    }
    
    SECTION("Orc stats") {
        retro_dungeon::Enemy orc(1, retro_dungeon::EnemyType::Orc, {0, 0});
        REQUIRE(orc.health == 40);
        REQUIRE(orc.attackPower == 10);
    }
    
    SECTION("Dragon has 0 health - bug") {
        retro_dungeon::Enemy dragon(1, retro_dungeon::EnemyType::Dragon, {0, 0});
        REQUIRE(dragon.health > 0);
    }
}

TEST_CASE("Enemy combat", "[enemy]") {
    retro_dungeon::Enemy enemy(1, retro_dungeon::EnemyType::Goblin, {5, 5});
    
    SECTION("Taking damage") {
        enemy.takeDamage(10);
        REQUIRE(enemy.health == 10);
    }
    
    SECTION("Death detection") {
        enemy.takeDamage(50);
        REQUIRE(!enemy.isAlive());
    }
}