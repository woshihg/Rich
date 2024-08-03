# 设置构建类型为Release
set(CMAKE_BUILD_TYPE "Release")

cmake_minimum_required(VERSION 3.24)
project(The_Rich)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

# 源文件列表
set(SOURCE_FILES
        main.cpp
        json/cJSON.cpp json/cJSON.h
        json/json.cpp json/json.h
        map/mapdraw.cpp map/mapdraw.h
        money/money.cpp money/money.h
        terminal/terminal.cpp terminal/terminal.h
        player/player.cpp
        tool/tool.cpp
        giftroom/gift.cpp giftroom/gift.h
        game/game.cpp game/game.h
        )

# 将源文件添加到可执行文件中
add_executable(The_Rich ${SOURCE_FILES})

# 添加头文件路径
include_directories(
        ${CMAKE_SOURCE_DIR}/json
        ${CMAKE_SOURCE_DIR}/map
        ${CMAKE_SOURCE_DIR}/money
        ${CMAKE_SOURCE_DIR}/terminal
        ${CMAKE_SOURCE_DIR}/player
        ${CMAKE_SOURCE_DIR}/tool
        ${CMAKE_SOURCE_DIR}/giftroom
        ${CMAKE_SOURCE_DIR}/game
)
