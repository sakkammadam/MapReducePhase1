cmake_minimum_required(VERSION 3.23)
project(scratchStuff)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.80.0/include/)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.80.0/lib/)
set(CMAKE_CXX_STANDARD 20)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Boost REQUIRED COMPONENTS log system)
add_executable(scratchStuff main.cpp FileProcessor.cpp FileProcessor.h Mapper.cpp Mapper.h)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    message("Boost VERSION: ${Boost_VERSION}")
    message("Boost INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message("Boost Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
    message("Boost LIBRARIES: ${Boost_LIBRARIES}")

    TARGET_LINK_LIBRARIES(scratchStuff ${Boost_LIBRARIES})
endif ()
