file(GLOB_RECURSE DREAMENGINE_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(DreamEngine STATIC ${DREAMENGINE_SOURCES})

target_include_directories(DreamEngine PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(DreamEngine
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer)
