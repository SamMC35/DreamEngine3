cmake_minimum_required(VERSION 3.20)
project(DreamEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        /opt/homebrew/include/SDL2_image
        /opt/homebrew/include/SDL2
        /opt/homebrew/opt/llvm/include/c++/v1
        ${CMAKE_SOURCE_DIR}/include
)

link_directories(/opt/homebrew/lib)

# Add engine sources
add_subdirectory(src)

# Add examples (games)
add_subdirectory(examples/OggyPokerGame)
add_subdirectory(examples/SpaceInvaders)
add_subdirectory(examples/Pong)

configure_file(${CMAKE_SOURCE_DIR}/8bit.ttf ${CMAKE_BINARY_DIR}/8bit.ttf COPYONLY)


# Optional: test build
add_executable(TestApp test.cpp)

#
#target_include_directories(TestApp PRIVATE include)
target_link_libraries(TestApp PRIVATE DreamEngine)
