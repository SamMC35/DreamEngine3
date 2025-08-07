file(GLOB_RECURSE INVADERS_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(SpaceInvaders ${INVADERS_SOURCES})

target_include_directories(SpaceInvaders PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(SpaceInvaders PRIVATE DreamEngine)
