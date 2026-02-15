#include <catch2/catch_all.hpp>
#include "retro_dungeon/game.hpp"

TEST_CASE("Combat damage calculation", "[combat]") {
    SECTION("Basic damage calculation") {
        int attack = 10;
        int defense = 4;
        int expected = 10 - (4 / 2);
        REQUIRE(expected == 8);
    }
    
    SECTION("Damage can be negative - bug") {
        int attack = 5;
        int defense = 20;
        int damage = attack - (defense / 2);
        REQUIRE(damage >= 0);
    }
}

TEST_CASE("Player vs Enemy combat", "[combat]") {
    retro_dungeon::Player player(1, "Hero", {5, 5});
    retro_dungeon::Enemy enemy(2, retro_dungeon::EnemyType::Goblin, {5, 5});
    
    SECTION("Player damages enemy") {
        int initialHealth = enemy.health;
        enemy.takeDamage(player.attackPower);
        REQUIRE(enemy.health == initialHealth - player.attackPower);
    }
    
    SECTION("Enemy damages player") {
        int initialHealth = player.health;
        player.takeDamage(enemy.attackPower);
        REQUIRE(player.health == initialHealth - enemy.attackPower);
    }
}