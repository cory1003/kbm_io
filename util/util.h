#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>
#include <unistd.h>
// #include <stdio.h> //perror

typedef void (*callback_t)(void*);

uint64_t get_time();
// uint64_t sdbm_hash_32bit( void * key );
// uint64_t sdbm_hash_string( void * key );

inline void ssleep( uint64_t seconds ){
    usleep(seconds*10e6);
}

inline void msec_sleep(int msec ){
    usleep(msec*10e3);
} 

#endif