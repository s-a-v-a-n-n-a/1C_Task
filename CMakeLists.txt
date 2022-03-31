cmake_minimum_required(VERSION 3.15)	# Проверка версии CMake.
project(checkers LANGUAGES CXX)			# Название проекта

set(CMAKE_CXX_COMPILER clang++-12)
set(CMAKE_CXX_STANDARD 20)

set(SFML_BUILD_GRAPHICS true)

set(DLL "-lsfml-graphics -lsfml-window -lsfml-system")
set(NO_OPT "-fno-elide-constructors")

set(CMAKE_CXX_FLAGS "-O3 -std=c++20 -Wall -fdeclspec -march=native")

set(SOURCE_EXE main.cpp)	# Установка переменной со списком исходников для исполняемого файла

include_directories("src/"
                    "src/Visualisation"
                    "src/Visualisation/sfml_drawing")

find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)


set(SOURCES src/Application.cpp
            src/Game.cpp
            src/Cell.cpp
            src/Checker.cpp
            src/Chessboard.cpp
            src/Player.cpp
            src/Bot.cpp
            src/Real_player.cpp
            src/Visualisation/sfml_drawing/screen_functions.cpp
            src/Visualisation/sfml_drawing/Renderer.cpp
            src/Visualisation/sfml_drawing/Texture.cpp
            src/Visualisation/sfml_drawing/colors.cpp)

add_executable(main ${SOURCE_EXE} ${SOURCES})

target_link_libraries(main sfml-graphics sfml-window sfml-system)
target_link_libraries(main ${CMAKE_DL_LIBS})
