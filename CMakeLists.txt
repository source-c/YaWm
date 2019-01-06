cmake_minimum_required(VERSION 3.7)
project(YaWm)

set(CMAKE_C_STANDARD 11)

if(APPLE)
    include_directories(AFTER "/opt/X11/include")
endif()

include_directories(.)
include_directories(dmenu)
include_directories(slock)
include_directories(st)
include_directories(status)
include_directories(wm)

