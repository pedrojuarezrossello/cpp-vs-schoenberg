cmake_minimum_required(VERSION 3.7.2)

project(Schoenberg VERSION 1.0
                  DESCRIPTION "Random twelve tone melody generator"
		LANGUAGES CXX)
				  
file(GLOB_RECURSE sources include/*.h lib/utils/*.h include/*.cpp)

add_executable(example ${sources})

set_target_properties(example PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
