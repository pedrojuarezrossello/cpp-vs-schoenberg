add_executable (include melody.h score.h time_signature.h tone_row.h utils/melody_utils.h utils/score_utils.h utils/tables.h utils/tone_row_utils.h utils/utils.h)

target_include_directories(include PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})