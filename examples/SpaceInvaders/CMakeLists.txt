file(GLOB_RECURSE INVADERS_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(SpaceInvaders ${INVADERS_SOURCES})

target_include_directories(SpaceInvaders PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

configure_file(${CMAKE_SOURCE_DIR}/8bit.ttf ${CMAKE_CURRENT_BINARY_DIR}/8bit.ttf COPYONLY)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/resources")

target_link_libraries(SpaceInvaders PRIVATE DreamEngine)
