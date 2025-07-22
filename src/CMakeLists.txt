cmake_minimum_required( VERSION 3.16 )


include_directories( PUBLIC ${CMAKE_SOURCE_DIR}
                     PUBLIC ${CMAKE_SOURCE_DIR}/include
                     PUBLIC ${CMAKE_SOURCE_DIR}/util
                       )

project( kbm-io )                       
add_library( kbm-io kbm_io.c )
target_link_libraries( kbm-io signal_handler )

project( auto-click )
add_executable( ${PROJECT_NAME} main.cpp input_record.cpp )


target_link_libraries( ${PROJECT_NAME} kbm-io util signal_handler Xtst X11 )
target_link_libraries( ${PROJECT_NAME} kbm-io util signal_handler Xtst X11 random)
# target_link_libraries( ${PROJECT_NAME} hashmap util signal_handler io_util ts_queue )
