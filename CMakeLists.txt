cmake_minimum_required(VERSION 3.20)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# Collect all .cpp files
file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/*.cpp
)

# Collect all include directories
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/examples/OggyPokerGame/include
        /opt/homebrew/include/SDL2
        /opt/homebrew/opt/llvm/include/c++/v1
)

# Define the executable
add_executable(MyProject ${SOURCES}
        examples/OggyPokerGame/include/ai_service.h
        examples/OggyPokerGame/include/player.h
        examples/OggyPokerGame/include/card_service.h)
