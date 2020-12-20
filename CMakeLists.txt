cmake_minimum_required(VERSION 3.17)
project(Library_Manager C)

set(CMAKE_C_STANDARD 99)

link_libraries(sqlite3)

add_executable(Library_Manager main.c)
