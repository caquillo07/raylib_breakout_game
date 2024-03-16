cmake_minimum_required(VERSION 3.27)
project(breakout_game C)

set(CMAKE_C_STANDARD 23)

file(GLOB SOURCES *.c *.h src/*.c src/*.h src/*/*.c src/*/*.h)
add_executable(breakout_game ${SOURCES})

target_compile_options(breakout_game PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(breakout_game PRIVATE -fsanitize=address)

find_package(raylib CONFIG REQUIRED)
if (APPLE)
    message("[APPLE] "  ${CMAKE_SYSTEM_NAME})
    target_link_libraries(breakout_game PRIVATE raylib "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
else()
    target_link_libraries(breakout_game PRIVATE raylib)
endif()

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(breakout_game PRIVATE glfw)
