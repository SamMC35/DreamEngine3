file(GLOB_RECURSE OGGY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(OggyPokerGame ${OGGY_SOURCES})

target_include_directories(OggyPokerGame PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include
)
configure_file(${CMAKE_SOURCE_DIR}/8bit.ttf ${CMAKE_CURRENT_BINARY_DIR}/8bit.ttf COPYONLY)


target_link_libraries(OggyPokerGame PRIVATE DreamEngine)