cmake_minimum_required(VERSION 3.1)

project(SlidingPuzzle)

set(CMAKE_BUILD_TYPE Release)

set(SFML_ROOT "/Software/SFML-2.2")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wfatal-errors -pedantic -pedantic-errors -mwindows")

include_directories(include)
set(SOURCE_FILES
    include/sliding_puzzle/component/exit_listener.h
    include/sliding_puzzle/component/fullscreen_listener.h
    include/sliding_puzzle/component/game.h
    include/sliding_puzzle/component/image.h
    include/sliding_puzzle/component/matrix.h
    include/sliding_puzzle/component/shuffleable_game.h
    include/sliding_puzzle/component/solvable_game.h
    include/sliding_puzzle/component/square_image.h
    include/sliding_puzzle/randomizer/min_distance.h
    include/sliding_puzzle/solver/idastar.h
    include/sliding_puzzle/solver/playback.h
    include/sliding_puzzle/app.h
    include/sliding_puzzle/component.h
    include/sliding_puzzle/coordinate_converter.h
    include/sliding_puzzle/move.h
    include/sliding_puzzle/pair.h
    include/sliding_puzzle/randomizer.h
    include/sliding_puzzle/sliding_puzzle.h
    include/sliding_puzzle/solver.h
    include/sliding_puzzle/state.h
    include/sliding_puzzle/unused.h
    include/sliding_puzzle/window.h
    src/main.cc)

set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SFML_STATIC_LIBRARIES ON)
find_package(SFML 2 REQUIRED graphics window system)
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_DEPENDENCIES})
else()
    message(SEND_ERROR "SFML library not found. Please set SFML_ROOT.")
endif()
