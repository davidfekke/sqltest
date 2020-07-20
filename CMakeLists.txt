cmake_minimum_required(VERSION 3.13)

project(sqltest)

add_executable(sqltest sqltest.c)
target_link_libraries(sqltest Sqlite3)