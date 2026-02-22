# Retro Dungeon Workshop

[![CI](https://github.com/anxkhn/retro-dungeon-workshop/actions/workflows/ci.yml/badge.svg)](https://github.com/anxkhn/retro-dungeon-workshop/actions/workflows/ci.yml)
[![Issues](https://img.shields.io/github/issues/anxkhn/retro-dungeon-workshop)](https://github.com/anxkhn/retro-dungeon-workshop/issues)
[![License](https://img.shields.io/github/license/anxkhn/retro-dungeon-workshop)](LICENSE)

**Educational Repository for Learning Open Source Contributions**

This repository contains intentionally seeded bugs designed to help new contributors learn the open source contribution workflow. It provides a safe, beginner-friendly environment to practice fixing issues, submitting pull requests, and collaborating with maintainers.

## Project Description

Retro Dungeon Workshop is a text-based roguelike game that runs entirely in the terminal. Explore procedurally generated dungeons, battle enemies, collect items, and survive as long as you can in this classic-style adventure game.

## Features

- **Procedural Dungeon Generation** - Every playthrough generates unique dungeon layouts with rooms, corridors, and hidden areas
- **Turn-Based Combat** - Strategic combat system with attack, defense, and special abilities
- **Inventory System** - Collect and manage items including weapons, armor, potions, and treasures
- **Save/Load System** - Persist your progress and continue your adventure later
- **Multiple Enemy Types** - Face various enemies with different behaviors and abilities
## Enemy Types

| Enemy | Symbol | Health | Attack | Defense |
|-------|--------|--------|--------|---------|
| Goblin | `g` | 20 | 5 | 2 |
| Orc | `o` | 40 | 10 | 5 |
| Skeleton | `s` | 25 | 8 | 3 |
| Zombie | `z` | 35 | 6 | 8 |
| Rat | `r` | 5 | 2 | 0 |
| Spider | `x` | 15 | 6 | 1 |
| Dragon | `D` | 200 | 30 | 20 |


- **Classic Roguelike Mechanics** - Permadeath, procedural generation, and strategic gameplay

## Learning Objectives

This project helps you learn:

- The complete open source contribution workflow
- Git branching and commit practices
- Code review processes
- Testing and continuous integration
- C++ best practices and modern C++20 features
- Working with CMake build systems

## Quick Start

### Prerequisites

- CMake 3.28 or higher
- C++20 compatible compiler (GCC 10+, Clang 10+, or MSVC 2019+)
- Git

### Build and Run

```bash
# Clone the repository
git clone https://github.com/anxkhn/retro-dungeon-workshop.git
cd retro-dungeon-workshop

# Configure and build
cmake -B build
cmake --build build

# Run the game
./build/bin/retro_dungeon
```

### Installing Dependencies

Catch2 is automatically fetched via CMake FetchContent during the build process. No manual installation required.

## Using github.dev

github.dev provides a browser-based VS Code environment for quick edits:

1. Navigate to the repository on GitHub
2. Press `.` (period) or change the URL from `github.com` to `github.dev`
3. Make your changes directly in the browser
4. Use the Source Control panel to commit and push changes
5. Create a pull request from your branch

This is ideal for small fixes and documentation updates without setting up a local development environment.

## Project Structure

```
retro-dungeon-workshop/
├── include/
│   └── retro_dungeon/
│       ├── core/           # Game engine and input handling
│       ├── entities/       # Player, enemy, and item classes
│       ├── systems/        # Combat, inventory, save systems
│       ├── utils/          # Logger, random, terminal utilities
│       └── world/          # Dungeon generation, map, room, tile
├── src/
│   ├── core/               # Engine implementation
│   ├── entities/           # Entity implementations
│   ├── systems/            # System implementations
│   ├── utils/              # Utility implementations
│   └── world/              # World generation implementations
├── tests/                  # Catch2 test files
├── docs/                   # Additional documentation
├── .github/                # GitHub workflows and templates
├── CMakeLists.txt          # Build configuration
└── .clang-format           # Code style configuration
```

## Running Tests

```bash
# Build the project first
cmake -B build
cmake --build build

# Run all tests
cd build && ctest

# Run with verbose output
cd build && ctest --output-on-failure

# Run specific test
./build/bin/test_retro_dungeon "[player]"
```

## Issue Labels

Issues are categorized by difficulty to help you find appropriate challenges:

| Label | Description |
|-------|-------------|
| `good-first-issue` | Beginner-friendly issues ideal for first contributors |
| `intermediate` | Moderate complexity, requires understanding of codebase |
| `advanced` | Complex issues requiring deep knowledge or architectural changes |

Additional labels include `bug`, `enhancement`, `documentation`, and `help-wanted`.

## Contributing

We welcome contributions! Please read [CONTRIBUTING.md](CONTRIBUTING.md) for detailed guidelines on:

- Setting up your development environment
- Creating branches and submitting pull requests
- Code style and testing requirements
- Commit message conventions

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
