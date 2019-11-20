cmake_minimum_required(VERSION 3.13)
project(3305ass2 C)

set(CMAKE_C_STANDARD 99)
#INCLUDE_DIRECTORIES(scheduling.h)
set(SOURCE_FILE part1.c)
#set(SOURCE_FILE assignment2_part1.c)
add_executable(3305ass2  ${SOURCE_FILE})