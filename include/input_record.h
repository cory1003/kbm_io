
#pragma once
#include <vector>
#include <cstring>
#include <iostream>
#include <stdint.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>


extern "C" {
   #include "include/kbm_io.h"
}


void* io_record(void* arg);
typedef void (*event_call_back_func)(event_log_t);


typedef struct record_struct{
    std::vector<char> buffer;
    record_struct(){
        buffer.resize(0);
    }
    template<typename DataType>
    friend record_struct& operator << (record_struct& record, const DataType& data){
        
        // Check that the type of the data being pushed is trivially copyable
        static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

        // Cache current size of vector, as this will be the point we insert the data
        size_t i = record.buffer.size();

        // Resize the vector by the size of the data being pushed
        record.buffer.resize( i + sizeof(DataType));

        // Physically copy the data into the newly allocated vector space
        std::memcpy(record.buffer.data() + i, &data, sizeof(DataType));
        std::cout << record.buffer.size() << std::endl;
        // Return the target message so it can be "chained"
        return record;
    }
} record_struct_t;




class Input_Recorder{
public:
    Input_Recorder();
    ~Input_Recorder();

   void poll_key_event();
   void poll_mouse_event();
   void monitor();
   void write_file( const char * file_name );
   bool _click_only;
   bool _monitor_keyboard;

private:

    void log_key( int event, int key );
    void log_mouse( int event );
    
    record_struct_t _record;
    bool _recording;
    uint64_t _last_event_time;
    int _prev_x, _prev_y;

    //X11 key and mouse variables
    Window root, root_return, child_return;
    int root_x, root_y, win_x, win_y;
    unsigned int mask_return;
    int old_button_state;
    int poll_type;
    // key event items
    XKeyEvent event;
    Display *display;
    char keys[32]; // Array to hold the state of the keys
    uint64_t old_keys[256];
    char key_map[256];
    event_call_back_func event_callback;

};