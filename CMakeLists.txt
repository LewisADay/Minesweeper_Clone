cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project("Minesweeper_Clone")
set(MINESWEEPER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME})

add_subdirectory("source")
add_subdirectory("vendor")

# Copy our resources to the binary location
add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/resources
                ${CMAKE_CURRENT_BINARY_DIR}/resources)
