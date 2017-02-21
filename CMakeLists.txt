cmake_minimum_required(VERSION 3.5)
project(Simulated_annealing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Board.cpp Board.h Annealing.cpp Annealing.h)
add_executable(Simulated_annealing ${SOURCE_FILES})