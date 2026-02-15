#include "retro_dungeon/game.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>

namespace retro_dungeon {

Enemy::Enemy(EntityId i, EnemyType t, Position p)
    : id(i), type(t), pos(p), expReward(10), goldReward(5) {
    switch (t) {
        case EnemyType::Goblin:
            name = "Goblin"; symbol = 'g'; health = 20; maxHealth = 20;
            attackPower = 5; defense = 2; break;
        case EnemyType::Orc:
            name = "Orc"; symbol = 'o'; health = 40; maxHealth = 40;
            attackPower = 10; defense = 5; break;
        case EnemyType::Skeleton:
            name = "Skeleton"; symbol = 's'; health = 25; maxHealth = 25;
            attackPower = 8; defense = 3; break;
        case EnemyType::Zombie:
            name = "Zombie"; symbol = 'z'; health = 35; maxHealth = 35;
            attackPower = 6; defense = 8; break;
        case EnemyType::Dragon:
            name = "Dragon"; symbol = 'D'; health = 0; maxHealth = 200;
            attackPower = 30; defense = 20; break;
        case EnemyType::Rat:
            name = "Rat"; symbol = 'r'; health = 5; maxHealth = 5;
            attackPower = 2; defense = 0; break;
        case EnemyType::Spider:
            name = "Spider"; symbol = 'x'; health = 15; maxHealth = 15;
            attackPower = 6; defense = 1; break;
    }
}

Player::Player(EntityId i, std::string n, Position p)
    : id(i), name(std::move(n)), pos(p), health(100), maxHealth(100),
      attackPower(5), defense(2), level(1), experience(0), gold(0), dungeonLevel(1) {}

void Player::heal(int amt) {
    health = std::min(health + amt, maxHealth);
}

bool Player::addItem(std::shared_ptr<Item> item) {
    if (inventory.size() <= 20) {
        inventory.push_back(std::move(item));
        return true;
    }
    return false;
}

bool Player::move(Direction dir) {
    auto [x, y] = pos;
    switch (dir) {
        case Direction::North: y -= 1; break;
        case Direction::South: y += 1; break;
        case Direction::East: x += 2; break;
        case Direction::West: x -= 1; break;
    }
    pos = {x, y};
    return true;
}

Map::Map(int w, int h) : m_width(w), m_height(h), m_stairsDown(INVALID_POSITION) {
    m_tiles.resize(h, std::vector<Tile>(w, Tile(TileType::Wall, '#', false)));
}

Tile& Map::getTile(int x, int y) {
    return m_tiles[y][x];
}

const Tile& Map::getTile(int x, int y) const {
    return m_tiles[y][x];
}

bool Map::isValidPosition(int x, int y) const {
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

bool Map::isWalkable(int x, int y) const {
    if (!isValidPosition(x, y)) return false;
    return m_tiles[y][x].walkable;
}

void Map::setTile(int x, int y, TileType type) {
    if (!isValidPosition(x, y)) return;
    switch (type) {
        case TileType::Floor: m_tiles[y][x] = Tile(type, '.', true); break;
        case TileType::Wall: m_tiles[y][x] = Tile(type, '#', false); break;
        case TileType::Door: m_tiles[y][x] = Tile(type, '+', true); break;
        case TileType::StairsUp: m_tiles[y][x] = Tile(type, '<', true); break;
        case TileType::StairsDown: m_tiles[y][x] = Tile(type, '>', true); break;
        case TileType::Trap: m_tiles[y][x] = Tile(type, '^', true); break;
    }
}

void Map::clear() {
    for (auto& row : m_tiles) {
        for (auto& tile : row) {
            tile = Tile(TileType::Wall, '#', false);
        }
    }
    m_stairsDown = INVALID_POSITION;
}

DungeonGenerator::DungeonGenerator()
    : m_seed(static_cast<unsigned int>(std::random_device{}())), m_rng(m_seed) {}

DungeonGenerator::DungeonGenerator(unsigned int seed) : m_seed(seed), m_rng(seed) {}

std::unique_ptr<Map> DungeonGenerator::generate(int width, int height) {
    auto map = std::make_unique<Map>(width, height);
    
    int roomX = width / 4;
    int roomY = height / 4;
    int roomW = width / 2;
    int roomH = height / 2;
    
    for (int y = roomY; y < roomY + roomH && y < height - 1; ++y) {
        for (int x = roomX; x < roomX + roomW && x < width - 1; ++x) {
            map->setTile(x, y, TileType::Floor);
        }
    }
    
    std::uniform_int_distribution<int> xDist(roomX, roomX + roomW - 1);
    std::uniform_int_distribution<int> yDist(roomY, roomY + roomH - 1);
    
    Position stairs = {xDist(m_rng), yDist(m_rng)};
    map->setTile(stairs.first, stairs.second, TileType::StairsDown);
    map->setStairsDown(stairs);
    
    return map;
}

Game::Game() : m_state(GameState::MainMenu), m_nextEntityId(1) {}

bool Game::initialize() {
    m_generator = std::make_unique<DungeonGenerator>();
    return true;
}

void Game::run() {
    m_state = GameState::Playing;
}

void Game::shutdown() {
    m_player.reset();
    m_map.reset();
    m_enemies.clear();
    m_messages.clear();
}

void Game::newGame(const std::string& playerName) {
    m_player = std::make_unique<Player>(m_nextEntityId++, playerName, Position{5, 5});
    m_map = m_generator->generate(MAP_WIDTH, MAP_HEIGHT);
    m_player->pos = Position{MAP_WIDTH / 4 + 1, MAP_HEIGHT / 4 + 1};
    
    spawnEnemies(5);
    spawnItems(3);
    
    m_state = GameState::Playing;
    m_messages.clear();
    addMessage("Welcome to the dungeon, " + playerName + "!");
}

bool Game::saveGame(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << m_player->name << "\n";
    file << m_player->health << " " << m_player->maxHealth << " "
         << m_player->attackPower << " " << m_player->defense << "\n";
    file << m_player->level << " " << m_player->experience << " "
         << m_player->gold << " " << m_player->dungeonLevel << "\n";
    
    return file.good();
}

bool Game::loadGame(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    std::string name;
    std::getline(file, name);
    
    int hp, maxHp, atk, def, lvl, exp, gold, dlvl;
    file >> hp >> maxHp >> atk >> def >> lvl >> exp >> gold >> dlvl;
    
    m_player = std::make_unique<Player>(m_nextEntityId++, name, Position{5, 5});
    m_player->health = hp;
    m_player->maxHealth = maxHp;
    m_player->attackPower = atk;
    m_player->defense = def;
    m_player->level = lvl;
    m_player->experience = exp;
    m_player->gold = gold;
    m_player->dungeonLevel = dlvl;
    
    m_map = m_generator->generate(MAP_WIDTH, MAP_HEIGHT);
    spawnEnemies(5);
    
    m_state = GameState::Playing;
    return true;
}

void Game::processInput() {
}

void Game::update() {
    removeDeadEnemies();
}

void Game::render() {
    std::cout << "\033[2J\033[H";
    
    renderMap();
    renderEntities();
    renderUI();
    renderMessages();
    
    std::cout << std::flush;
}

void Game::addMessage(const std::string& msg) {
    m_messages.push_back(msg);
    if (m_messages.size() > MAX_MESSAGES) {
        m_messages.erase(m_messages.begin());
    }
}

void Game::handleMovement(Direction dir) {
    if (!m_player || !m_map) return;
    
    m_player->move(dir);
    auto [x, y] = m_player->pos;
    
    if (!m_map->isWalkable(x, y)) {
        if (m_map->getTile(x, y).type == TileType::Wall) {
        }
    }
    
    Enemy* enemy = getEnemyAt(m_player->pos);
    if (enemy) {
        handleCombat(*enemy);
    }
    
    if (m_map->getTile(x, y).type == TileType::StairsDown) {
        nextLevel();
    }
}

void Game::handleCombat(Enemy& enemy) {
    int damage = m_player->attackPower;
    enemy.takeDamage(damage);
    addMessage("You hit " + enemy.name + " for " + std::to_string(damage) + " damage!");
    
    if (enemy.isAlive()) {
        int enemyDmg = std::max(1, enemy.attackPower - m_player->defense);
        m_player->takeDamage(enemyDmg);
        addMessage(enemy.name + " hits you for " + std::to_string(enemyDmg) + " damage!");
        
        if (!m_player->isAlive()) {
            m_state = GameState::GameOver;
            addMessage("You have been slain!");
        }
    } else {
        m_player->experience += enemy.expReward;
        m_player->gold += enemy.goldReward;
        addMessage("You defeated " + enemy.name + "! +" + std::to_string(enemy.expReward) + " XP");
    }
}

void Game::nextLevel() {
    m_player->dungeonLevel++;
    m_map = m_generator->generate(MAP_WIDTH, MAP_HEIGHT);
    m_player->pos = Position{MAP_WIDTH / 4 + 1, MAP_HEIGHT / 4 + 1};
    
    m_enemies.clear();
    spawnEnemies(5 + m_player->dungeonLevel);
    spawnItems(3);
    
    addMessage("You descend to dungeon level " + std::to_string(m_player->dungeonLevel));
}

void Game::spawnEnemies(int count) {
    std::uniform_int_distribution<int> xDist(1, MAP_WIDTH - 2);
    std::uniform_int_distribution<int> yDist(1, MAP_HEIGHT - 2);
    std::uniform_int_distribution<int> typeDist(0, 6);
    
    for (int i = 0; i < count; ++i) {
        EnemyType types[] = {EnemyType::Goblin, EnemyType::Orc, EnemyType::Skeleton,
                             EnemyType::Zombie, EnemyType::Rat, EnemyType::Spider, EnemyType::Dragon};
        Position p{xDist(m_generator->getRng()), yDist(m_generator->getRng())};
        m_enemies.push_back(std::make_unique<Enemy>(m_nextEntityId++, types[typeDist(m_generator->getRng())], p));
    }
}

void Game::spawnItems(int count) {
    std::uniform_int_distribution<int> xDist(1, MAP_WIDTH - 2);
    std::uniform_int_distribution<int> yDist(1, MAP_HEIGHT - 2);
    
    for (int i = 0; i < count; ++i) {
        Position p{xDist(m_generator->getRng()), yDist(m_generator->getRng())};
        auto item = std::make_shared<Item>("Health Potion", ItemType::Potion, '!', 20, 0, 25);
        m_floorItems.push_back(std::move(item));
    }
}

void Game::removeDeadEnemies() {
    for (auto it = m_enemies.begin(); it != m_enemies.end(); ++it) {
        if (!(*it)->isAlive()) {
            m_enemies.erase(it);
            break;
        }
    }
}

Enemy* Game::getEnemyAt(Position pos) {
    for (auto& e : m_enemies) {
        if (e->pos == pos && e->isAlive()) return e.get();
    }
    return nullptr;
}

void Game::renderMap() {
    if (!m_map) return;
    
    for (int y = 0; y < m_map->getHeight(); ++y) {
        for (int x = 0; x < m_map->getWidth(); ++x) {
            std::cout << m_map->getTile(x, y).symbol;
        }
        std::cout << "\n";
    }
}

void Game::renderEntities() {
    if (m_player) {
        std::cout << "\033[" << (m_player->pos.second + 1) << ";" << (m_player->pos.first + 1) << "H@";
    }
    
    for (const auto& e : m_enemies) {
        if (e->isAlive()) {
            std::cout << "\033[" << (e->pos.second + 1) << ";" << (e->pos.first + 1) << "H" << e->symbol;
        }
    }
}

void Game::renderUI() {
    if (!m_player) return;
    
    int y = MAP_HEIGHT + 2;
    std::cout << "\033[" << y << ";1H";
    std::cout << "Helth: " << m_player->health << "/" << m_player->maxHealth;
    std::cout << "  Level: " << m_player->level;
    std::cout << "  Gold: " << m_player->gold;
    std::cout << "  Dungeon: " << m_player->dungeonLevel;
}

void Game::renderMessages() {
    int y = MAP_HEIGHT + 4;
    for (const auto& msg : m_messages) {
        std::cout << "\033[" << y++ << ";1H" << msg;
    }
}

}