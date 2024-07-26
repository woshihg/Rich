cmake_minimum_required(VERSION 3.24)
project(The_Rich)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(The_Rich main.cpp json/cJSON.cpp json/cJSON.h json/json.cpp json/json.h init/init.cpp init/init.h)
