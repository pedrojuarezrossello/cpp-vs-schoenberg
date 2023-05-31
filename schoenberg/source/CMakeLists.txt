add_executable(source melody_utils.cpp score_utils.cpp tone_row.cpp tone_row_utils.cpp utils.cpp)

target_include_directories (source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})