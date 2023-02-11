cmake_minimum_required(VERSION 2.8.3)

project(FiratQt)

include_directories(headers,D:\Qt\5.14.2\5.14.2\mingw73_64\include)
link_directories(D:\Qt\5.14.2\5.14.2\mingw73_64\lib)

set(CMAKE_AUTOMOC ON)
CONFIG += release

add_executable(bin/FirstQt.exe
                src/main.cpp 
                src/some_file.cpp)