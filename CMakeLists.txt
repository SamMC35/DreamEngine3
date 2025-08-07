cmake_minimum_required(VERSION 3.20)
project(OggyPokerGame)

set(CMAKE_CXX_STANDARD 17)

# Collect all .cpp files
file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/examples/OggyPokerGame/src/*.cpp

)

# Collect all include directories
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/examples/OggyPokerGame/include
        /opt/homebrew/include/SDL2_image
        /opt/homebrew/include/SDL2
        /opt/homebrew/opt/llvm/include/c++/v1
)
configure_file(${CMAKE_SOURCE_DIR}/8bit.ttf ${CMAKE_BINARY_DIR}/8bit.ttf COPYONLY)

link_directories(/opt/homebrew/lib)

# Define the executable
add_executable(OggyPokerGame ${SOURCES}
#        examples/OggyPokerGame/include/ai_service.h
#        examples/OggyPokerGame/include/player.h
#        examples/OggyPokerGame/include/card_service.h)
)



target_link_libraries(OggyPokerGame
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer)