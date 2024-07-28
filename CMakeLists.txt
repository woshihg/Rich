cmake_minimum_required(VERSION 3.24)
project(The_Rich)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(The_Rich main.cpp json/cJSON.cpp json/cJSON.h json/json.cpp json/json.h init/init.cpp init/init.h
        map/mapdraw.cpp
        map/mapdraw.h
        money/money.cpp
        money/money.h
        terminal/terminal.cpp
        terminal/terminal.h
        player/player.cpp
        tool/tool.cpp
        magic/magic.cpp
        magic/magic.h
        giftroom/gift.cpp
        giftroom/gift.h)
