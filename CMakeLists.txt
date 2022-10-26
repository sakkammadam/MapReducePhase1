cmake_minimum_required(VERSION 3.23)
project(MapReducePhase1)
set(CMAKE_CXX_STANDARD 17)

add_executable(main.cpp FileProcessor.cpp FileProcessor.h Mapper.cpp Mapper.h Shuffler.cpp Shuffler.h Reducer.cpp Reducer.h)