#include "retro_dungeon/game.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    retro_dungeon::Game game;
    
    if (!game.initialize()) {
        std::cerr << "Failed to initialize game" << std::endl;
        return 1;
    }
    
    std::cout << "Retro Dungeon v1.0.0" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter your name: ";
    
    std::string name;
    std::getline(std::cin, name);
    
    if (name.empty()) {
        name = "Adventurer";
    }
    
    game.newGame(name);
    game.run();
    game.render();
    
    std::cout << std::endl;
    std::cout << "Game initialized successfully!" << std::endl;
    std::cout << "This is a workshop repository for learning open source contributions." << std::endl;
    std::cout << "See the issues tab for tasks to practice." << std::endl;
    
    game.shutdown();
    return 0;
}