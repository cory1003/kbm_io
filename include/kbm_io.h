#pragma once
#include <stdint.h>
#include <stdbool.h>
const uint32_t MAX_FILE_PATH_SIZE = 256;


typedef struct kbm_io{
    char script_name[256];
    uint32_t mode;

    double click_delay;
    double click_delay_std_dev; 
    double script_delay;

    bool click_only; //only record mouse clicks

    uint32_t num_iterations;

} kbm_io_t;



enum event_id { KEY_PRESS, KEY_RELEASE, MOUSE_MOVE,\
             MOUSE_L_PRESS, MOUSE_R_PRESS, MOUSE_L_RELEASE, MOUSE_R_RELEASE, WAIT };

typedef struct event_log{
    uint32_t wait;
    uint16_t event;
    uint16_t key;
    uint16_t x;
    uint16_t y;
    
} event_log_t;

typedef void (*script_loop_callback_t)(event_log_t);

void set_script_loop_callback(script_loop_callback_t callback );
int run_script( char const* file_path, kbm_io_t io );
void set_mouse( int event );
uint32_t get_mouse_x();
void execute_event( event_log_t event_log );
