/**
 * @file sort.h
 * @author Cory Barrett 
 * @brief generic sorting algorithms
 * @version 0.1
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdint.h>



// TODO !! create macro to autogenerate merge sorts for all
// integer and floating point types

void merge_sort_uint64( uint64_t* arr, uint64_t len ); 
void merge_sort_uint32( uint32_t* arr, uint64_t len ); 
