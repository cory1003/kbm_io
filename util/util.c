#include "util.h"
#include <sys/time.h> //gettimeofday
#include <stdlib.h>
#include <stdio.h> //perror

uint64_t get_time(){ 
  struct timeval curr_time;
  gettimeofday(&curr_time, NULL);
  return curr_time.tv_sec * 1000000 + curr_time.tv_usec;
}




// uint64_t sdbm_hash_32bit( void * key ){
//   uint64_t hash = 5381;
//   char * p_key = (char *)(key);
//   for( uint64_t i = 0; i < sizeof(uint32_t); i++ ){
//     hash = (p_key[i]) + (hash << 6) + (hash << 16) - hash;
//   }

//   return hash;
// }

// uint64_t sdbm_hash_string( void * key ){
//   uint64_t hash = 5381;
//   char * p_key = (char *)(key);
//   while( p_key ){
//     hash = (*p_key) + (hash << 6) + (hash << 16) - hash;
//     p_key++;
//   }
//   return hash;
// }


