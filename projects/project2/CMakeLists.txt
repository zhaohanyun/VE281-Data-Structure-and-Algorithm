cmake_minimum_required(VERSION 3.12)
project(project2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wconversion -pedantic")

add_executable(project2 main.cpp hashtable.hpp hash_prime.hpp)