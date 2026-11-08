cmake_minimum_required(VERSION 3.20)
project(MatchingEngine VERSION 0.1.0 LANGUAGES CXX)

# C++20 estricto, sin extensiones de GNU
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Genera compile_commands.json para el autocompletado de VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------- librería con la lógica ------------
add_library(orderbook src/match.cpp)
target_include_directories(orderbook PUBLIC include)
target_compile_options(orderbook PRIVATE -Wall -Wextra -Wpedantic -Werror)

#---------- Ejecutable --------------
add_executable(orderbook_app src/main.cpp)
target_link_libraries(orderbook_app PRIVATE orderbook)

#----------- GoogleTest ----------
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

#---------- Tests ------------
enable_testing()
add_executable(orderbook_tests tests/match_test.cpp)
target_link_libraries(orderbook_tests PRIVATE orderbook GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(orderbook_tests)


