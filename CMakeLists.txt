cmake_minimum_required(VERSION 3.14)
project(PlatformerSFML)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/Objects/Gameobjects.cpp src/Objects/Gameobjects.h src/Objects/Player.cpp src/Objects/Player.h src/GameControlling/Gamestates.h src/Vector2.cpp src/Vector2.h src/Objects/Tile.cpp src/Objects/Tile.h src/GameControlling/Layout/Layout.h src/GameControlling/Layout/Layout.cpp src/GameControlling/Layout/Level.cpp src/GameControlling/Layout/Level.h src/GameControlling/Backgrounds.cpp src/GameControlling/Backgrounds.h src/Objects/Stars.cpp src/Objects/Stars.h src/Objects/Enemies.cpp src/Objects/Enemies.h src/Objects/Rigidbody.cpp src/Objects/Rigidbody.h src/GameControlling/Layout/TopLayer.cpp src/GameControlling/Layout/TopLayer.h src/GameControlling/Layout/Menu.cpp src/GameControlling/Layout/Menu.h src/GameControlling/Setting.h src/GameControlling/Layout/EndState.cpp src/GameControlling/Layout/EndState.h src/GameControlling/Layout/Time.h src/GameControlling/Layout/Time.cpp src/Objects/Bullet.cpp src/Objects/Bullet.h src/GameControlling/Abilities.h src/FileHandling.h src/FileHandling.cpp src/GameControlling/Layout/Highscore.cpp src/GameControlling/Layout/Highscore.h)
add_executable(PlatformerSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (PlatformerSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)