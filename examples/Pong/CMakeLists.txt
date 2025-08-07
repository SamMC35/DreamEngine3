file(GLOB_RECURSE PONG_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(PongGame ${PONG_SOURCES})

target_include_directories(PongGame PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

configure_file(${CMAKE_SOURCE_DIR}/8bit.ttf ${CMAKE_CURRENT_BINARY_DIR}/8bit.ttf COPYONLY)

target_link_libraries(PongGame PRIVATE DreamEngine)
