cmake_minimum_required(VERSION 3.12)
project(project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(project2 main.cpp utilities.cpp utilities.h Value.h data_point.h cluster.cpp cluster.h hash_func.cpp hash_func.h Hash_table.cpp Hash_table.h constants.h)