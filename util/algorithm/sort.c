#include "sort.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // memcpy
static void merge_sort_uint64_helper(uint64_t * src, uint64_t * dest,  uint64_t len);
static void merge_sort_uint32_helper(uint32_t * src, uint32_t * dest,  uint64_t len);

/**
 * @brief uses merge sort to sort array.
 *        sorted array will be in the same memory as src.
 *        Warning, 2X array memory overhead.
 *
 * @param arr array to be sorted
 * @param len length of arr
 */
void merge_sort_uint64( uint64_t* arr, uint64_t len ){
    if( len <= 1 ){return;}
    uint64_t* copy_arr = malloc(len*sizeof(uint64_t));
    memcpy(copy_arr, arr, len*sizeof(uint64_t));
    merge_sort_uint64_helper( copy_arr, arr, len);
    free(copy_arr);
}


/**
 * @brief private helper function to do the actual merge sorting,
          calling function is responsible for allocating  and freeing
          dest array.
 *
 *
 * @param src
 * @param dest
 * @param len
 */
void merge_sort_uint64_helper(uint64_t * src, uint64_t * dest,  uint64_t len)
{

    if(len == 1 ){
      return;
    }

    /*
      swap dest and src parameters between each call. This makes it
      easier to avoid copying arrays back to the original after
      each sort as well as having to allocate a new array during each
      recursive call.

      src will return two sorted halves ( left and right)
      which are then merge sorted into the destination (dest) arr,
      dest then becomes the calling functions sorted src array.
      when src matches the origiranal array to be sorted durring the initial
      function call, the original array will fully sorted when the last function
      returns.
    */

    // cache ((array length) / 2) to save calculation time 
    // right shift less expensive than an actual division
    uint64_t half_len = (len>>1);
    merge_sort_uint64_helper( dest, src, half_len);
    // merge_sort_uint64_helper( dest + (len>>1), src + (len>>1), len - (len>>1) );
    merge_sort_uint64_helper( dest + half_len, src + half_len, len - half_len );

    uint64_t * left = src;
    uint64_t * l_end = src + ((len>>1)-1);
    uint64_t * right = src + (len>>1);
    uint64_t * end = src + len-1;
    int i = 0;

    while(right && left ){
        if(*left < *right){
            // not as readable, but thre is a 5-10 % time
            // savings with 2^23 items by incrementing both
            // pointers at the same time.
            dest[i++] = *(left++);
            //i++;
            //left++;
            if( left > l_end ){
                left = NULL;
                src = right;
                // end = end;
                break;
            }
        }else{
            dest[i++] = *(right++);
            // i++;
            // right++;
            if( right > end ){
                right = NULL;
                src = left;
                end = l_end;
                break;
            }
        }
    }

    while(src <= end ){
        dest[i] = *src;
        i++;
        src++;
    }

}


void merge_sort_uint32( uint32_t* arr, uint64_t len ){
    if( len <= 1 ) return;
    uint32_t* copy_arr = malloc(len*sizeof(uint32_t));
    memcpy(copy_arr, arr, len*sizeof(uint32_t));
    merge_sort_uint32_helper( copy_arr, arr, len);
    free(copy_arr);
}

void merge_sort_uint32_helper(uint32_t * src, uint32_t * dest,  uint64_t len){

    if(len == 1 ){
      return;
    }

    //cache ((array length) / 2) to save calculation time
    uint64_t half_len = (len>>1);
    merge_sort_uint32_helper( dest, src, half_len);
    // merge_sort_uint64_helper( dest + (len>>1), src + (len>>1), len - (len>>1) );
    merge_sort_uint32_helper( dest + half_len, src + half_len, len - half_len );

    uint32_t * left = src;
    uint32_t * l_end = src + ((len>>1)-1);
    uint32_t * right = src + (len>>1);
    uint32_t * end = src + len-1;
    int i = 0;

    while(right && left ){
        if(*left < *right){
            // not as readable, but thre is a 5-10 % time
            // savings with 2^23 items by incrementing both
            // pointers at the same time.
            dest[i++] = *(left++);
            //i++;
            //left++;
            if( left > l_end ){
                left = NULL;
                src = right;
                // end = end;
                break;
            }
        }else{
            dest[i++] = *(right++);
            // i++;
            // right++;
            if( right > end ){
                right = NULL;
                src = left;
                end = l_end;
                break;
            }
        }
    }
    while(src <= end ){
        dest[i] = *src;
        i++;
        src++;
    }
}
