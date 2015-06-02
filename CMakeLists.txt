cmake_minimum_required(VERSION 2.8.4)
project(ir)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
            "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")        
    SET(warnings "-Wall -Wextra -Werror")
ENDIF ()

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

IF (APPLE)
    SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/local/include/")
    SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/usr/local/lib/")
ENDIF (APPLE)

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
   INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
   ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


ADD_SUBDIRECTORY(src)

add_executable(indexer index.cpp)
add_executable(searcher searcher.cpp)

target_link_libraries(indexer z htmlcxx index parser reader search util)
target_link_libraries(searcher z index parser search util)
