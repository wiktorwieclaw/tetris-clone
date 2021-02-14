file(GLOB SOURCE "*.*")
list(REMOVE_ITEM SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(src ${SOURCE})
add_executable(demo main.cpp)

target_link_libraries(src
        gxng
        lodepng
        ${CONAN_LIBS}
        glad
        )

target_link_libraries(demo src)
