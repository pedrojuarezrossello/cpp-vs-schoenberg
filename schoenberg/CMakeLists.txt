cmake_minimum_required(VERSION 3.7.2)

project(Schoenberg VERSION 1.0
                  DESCRIPTION "Random twelve tone melody generator"
                  LANGUAGES CPP)
				  
set(CPP_VERSION 20)

add_subdirectory(include) 
add_subdirectory(source)
