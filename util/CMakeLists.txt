cmake_minimum_required( VERSION 3.16 )

project( util )

# add_subdirectory( io )
# add_subdirectory( hashmap )
add_subdirectory( algorithm )
add_subdirectory( signal_handler )

add_library( util util.c )
 