cmake_minimum_required(VERSION 3.19)
project(Turing)

set(CMAKE_CXX_STANDARD 14)

add_executable(turing main.cpp TM.cpp TM.h)