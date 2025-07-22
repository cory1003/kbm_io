cmake_minimum_required( VERSION 3.16 )
include_directories(
                     PUBLIC ${CMAKE_SOURCE_DIR}/util
                    )
                    
project( util_sort )

add_library( util_sort sort.c )
add_library( random random.c random.h )