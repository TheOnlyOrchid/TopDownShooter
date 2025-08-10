cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp "src/include/config.h" "src/include/utils.h" "src/utils.cpp" "src/include/assetmanager.h" "src/assetmanager.cpp" "src/include/player.h" "src/player.cpp" "src/include/bullet.h" "src/bullet.cpp" "src/include/game.h" "src/game.cpp" "src/enemy.cpp" "src/include/enemy.h")
include_directories(src/include)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
