cmake_minimum_required(VERSION 3.7.2)

project(Schoenberg VERSION 1.0
                  DESCRIPTION "Random twelve tone melody generator"
                  LANGUAGES CXX)
				  
file(GLOB_RECURSE sources lib/*.h lib/utils/*.h src/*.cpp)

add_executable(example ${sources})

target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
