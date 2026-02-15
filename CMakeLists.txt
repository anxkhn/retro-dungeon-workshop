cmake_minimum_required(VERSION 3.28)

project(RetroDungeon
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "A text-based roguelike game for learning open source contributions"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(retro_dungeon
    src/main.cpp
    src/game.cpp
)

target_include_directories(retro_dungeon PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(retro_dungeon PRIVATE cxx_std_20)

enable_testing()

add_executable(test_retro_dungeon
    tests/test_main.cpp
    tests/test_player.cpp
    tests/test_enemy.cpp
    tests/test_map.cpp
    tests/test_combat.cpp
    tests/test_save.cpp
    tests/test_random.cpp
    src/game.cpp
)

target_include_directories(test_retro_dungeon PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(test_retro_dungeon PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(test_retro_dungeon)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT}
            -i
            -style=file
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
        COMMENT "Formatting source files"
    )
endif()