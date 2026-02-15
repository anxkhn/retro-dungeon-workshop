#ifndef RETRO_DUNGEON_GAME_HPP
#define RETRO_DUNGEON_GAME_HPP

#include "retro_dungeon/types.hpp"
#include <vector>
#include <memory>
#include <string>
#include <random>

namespace retro_dungeon {

struct Tile {
    TileType type = TileType::Wall;
    char symbol = '#';
    bool walkable = false;
    bool explored = false;
    bool visible = false;
    
    Tile() = default;
    Tile(TileType t, char s, bool w) : type(t), symbol(s), walkable(w) {}
};

struct Item {
    std::string name;
    ItemType type;
    char symbol;
    int value;
    int damage;
    int healAmount;
    
    Item(std::string n, ItemType t, char s, int v, int d = 0, int h = 0)
        : name(std::move(n)), type(t), symbol(s), value(v), damage(d), healAmount(h) {}
};

struct Enemy {
    EntityId id;
    std::string name;
    EnemyType type;
    Position pos;
    char symbol;
    int health;
    int maxHealth;
    int attackPower;
    int defense;
    int expReward;
    int goldReward;
    
    Enemy(EntityId i, EnemyType t, Position p);
    
    bool isAlive() const { return health > 0; }
    void takeDamage(int dmg) { health -= dmg; }
};

struct Player {
    EntityId id;
    std::string name;
    Position pos;
    int health;
    int maxHealth;
    int attackPower;
    int defense;
    int level;
    int experience;
    int gold;
    int dungeonLevel;
    std::vector<std::shared_ptr<Item>> inventory;
    
    Player(EntityId i, std::string n, Position p);
    
    bool isAlive() const { return health > 0; }
    void takeDamage(int dmg) { health -= dmg; }
    void heal(int amt);
    bool addItem(std::shared_ptr<Item> item);
    bool move(Direction dir);
};

class Map {
public:
    Map(int w, int h);
    
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    
    Tile& getTile(int x, int y);
    const Tile& getTile(int x, int y) const;
    
    bool isValidPosition(int x, int y) const;
    bool isWalkable(int x, int y) const;
    
    void setTile(int x, int y, TileType type);
    
    Position getStairsDown() const { return m_stairsDown; }
    void setStairsDown(Position p) { m_stairsDown = p; }
    
    void clear();
    
private:
    int m_width;
    int m_height;
    std::vector<std::vector<Tile>> m_tiles;
    Position m_stairsDown;
};

class DungeonGenerator {
public:
    DungeonGenerator();
    explicit DungeonGenerator(unsigned int seed);
    
    std::unique_ptr<Map> generate(int width, int height);
    std::mt19937& getRng() { return m_rng; }
    
private:
    unsigned int m_seed;
    std::mt19937 m_rng;
    
    void generateRooms(Map& map);
    void generateCorridors(Map& map);
    Position findValidPosition(const Map& map);
};

class Game {
public:
    Game();
    ~Game() = default;
    
    bool initialize();
    void run();
    void shutdown();
    
    GameState getState() const { return m_state; }
    Player* getPlayer() { return m_player.get(); }
    Map* getMap() { return m_map.get(); }
    
    void newGame(const std::string& playerName);
    bool saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);
    
    void processInput();
    void update();
    void render();
    
    void addMessage(const std::string& msg);
    const std::vector<std::string>& getMessages() const { return m_messages; }
    
    void handleMovement(Direction dir);
    void handleCombat(Enemy& enemy);
    void nextLevel();
    
private:
    GameState m_state;
    std::unique_ptr<Player> m_player;
    std::unique_ptr<Map> m_map;
    std::unique_ptr<DungeonGenerator> m_generator;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    std::vector<std::shared_ptr<Item>> m_floorItems;
    std::vector<std::string> m_messages;
    EntityId m_nextEntityId;
    
    void spawnEnemies(int count);
    void spawnItems(int count);
    void removeDeadEnemies();
    Enemy* getEnemyAt(Position pos);
    
    void renderMap();
    void renderEntities();
    void renderUI();
    void renderMessages();
    
    static constexpr int MAX_MESSAGES = 5;
    static constexpr int MAP_WIDTH = 60;
    static constexpr int MAP_HEIGHT = 20;
};

}

#endif