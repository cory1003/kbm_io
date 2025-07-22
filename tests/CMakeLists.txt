cmake_minimum_required( VERSION 3.16 )

project( unit_tests )
include_directories( PUBLIC ${CMAKE_SOURCE_DIR}
                  PUBLIC ${CMAKE_SOURCE_DIR}/util)

add_executable(test_hashmap test_hashmap.c)
target_link_libraries(test_hashmap hashmap util_sort)
