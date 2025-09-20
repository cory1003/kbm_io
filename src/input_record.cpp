#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <fstream>
#include <vector>
#include <cstring> //memcopy
#include <cstdlib> // For getenv

#include <iostream>
#include "include/input_record.h"
extern "C" {
   #include "util/util.h"
   #include "util/signal_handler/signal_handler.h"
   #include "include/kbm_io.h"
}

// enum event_id { KEY_PRESS, KEY_RELEASE, MOUSE_MOVE,\
//              MOUSE_L_PRESS, MOUSE_R_PRESS, MOUSE_L_RELEASE, MOUSE_R_RELEASE, WAIT };




// typedef struct event_log{
//     uint32_t wait;
//     uint16_t event;
//     uint16_t key;
//     uint16_t x;
//     uint16_t y;
    
// } event_log_t;






Input_Recorder::Input_Recorder(){
    
    event_callback = NULL;
    this->_click_only = false;
    this->_monitor_keyboard = true; 
    this->_recording = false;

    for( int a=0; a<256; a++ ){
        old_keys[a] =false;
    }
    // Open the display
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
    }
    event.display = display;
    event.window = DefaultRootWindow(display);
    event.root = DefaultRootWindow(display);
    event.subwindow = None;
    event.time = CurrentTime;
    event.x = 0;
    event.y = 0;
    event.x_root = 0;
    event.y_root = 0;
    event.state = 0;

    root = DefaultRootWindow(display);

    this->_last_event_time = -1;

}

Input_Recorder::~Input_Recorder(){
    XCloseDisplay(display);
}

void Input_Recorder::poll_mouse_event(){
    int root_x, root_y;
    XQueryPointer(display, root, &root_return, &child_return, &root_x, &root_y, &win_x, &win_y, &mask_return);

    // Check mouse button state
    int button_state = mask_return; // This will contain the state of the mouse buttons

    // Check for mouse button presses
    if ((button_state & Button1Mask) && !(old_button_state & Button1Mask)) {
        log_mouse( MOUSE_L_PRESS );
    }
    if (!(button_state & Button1Mask) && (old_button_state & Button1Mask)) {
        log_mouse( MOUSE_L_RELEASE );
        this->_recording = true;
    }

    // Repeat for other mouse buttons if needed
    if ((button_state & Button2Mask) && !(old_button_state & Button2Mask)) {
        std::cout << "Mouse button 2 pressed at (" << root_x << ", " << root_y << ")" << std::endl;
    }

    if (!(button_state & Button2Mask) && (old_button_state & Button2Mask)) {
        std::cout << "Mouse button 2 released at (" << root_x << ", " << root_y << ")" << std::endl;
    }
    // Repeat for other mouse buttons if needed
    if ((button_state & Button3Mask) && !(old_button_state & Button3Mask)) {
        std::cout << "Mouse button 3 pressed at (" << root_x << ", " << root_y << ")" << std::endl;
    }

    if (!(button_state & Button3Mask) && (old_button_state & Button3Mask)) {
        std::cout << "Mouse button 3 released at (" << root_x << ", " << root_y << ")" << std::endl;
    }

    if( !(this->_click_only)  && ((root_x != this->_prev_x) || (root_y != this->_prev_y)) ){
        
        this->_prev_x = root_x;
        this->_prev_y = root_y;
        log_mouse( MOUSE_MOVE );
    }

    // Update old button state
    old_button_state = button_state;
}


void Input_Recorder::poll_key_event(){

    // Query the current state of the keyboard
    XQueryKeymap(display, keys);
    auto event_time = get_time();
    bool add_wait_time = false;
    // Check each key in the keys array
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 8; j++) {
            
            int keycode = (i * 8) + j;
            if (keys[i] & (1 << j)) {
                
                int keycode = (i * 8) + j;
                if( old_keys[keycode] ){
                    continue;
                }else{
                    old_keys[keycode] = event_time;
                }
                // Calculate the keycode
                event.keycode = keycode;

                KeySym keysym = XLookupKeysym(&event, 0);
                key_map[keycode] = keysym;
                
                std::cout << "Key " << key_map[keycode] << " is currently pressed. Keycode: " << keycode << std::endl;
                 

                if( keysym == '6' ){
                    std::cout << "Key exit\n";
                    set_exit_flag( true);
                    return;
                }
            }else if( old_keys[keycode] ){
                auto time = get_time();
                
                std::cout << "Key \'" << key_map[keycode] << "\' released. keycode " << keycode << " duration: "<<  (time - old_keys[keycode])/1000.0 << std::endl;
                old_keys[keycode] = 0;
            }
            
        }
    }

}


void Input_Recorder::log_key( int event, int key ){
    uint64_t time = get_time();
    
    event_log_t log; 
    log.event = event;
    log.key = key;
    log.wait = uint32_t(time - this->_last_event_time);
    this->_last_event_time = time;
    this->_record << log; 
}

void Input_Recorder::log_mouse( int event ){
    
    uint64_t time = get_time();
    if( this->_click_only && event == MOUSE_MOVE ){
        return;
    }
    if( this->_last_event_time == -1 ){
        this->_last_event_time = time;
    }

    if(this->_recording == false){
        this->_last_event_time = time;
        return;
    } 

    std::cout << "logging" << std::endl;
    event_log_t log;
    log.wait = uint32_t(time - this->_last_event_time);
    std::cout << "wait:" << log.wait<< std::endl;
    this->_last_event_time = time;
    log.event = event;
    log.x = this->_prev_x;
    log.y = this->_prev_y;
    this->_record << log;

    
}


static bool stop_mouse_record = false;
char key_map[256] = {0};



void* io_record(void* arg){
    kbm_io_t io = *((kbm_io_t*)(arg));

    static Input_Recorder ir;
    ir._click_only = io.click_only;
    while (!should_exit()){
        ir.poll_key_event();
        ir.poll_mouse_event();
        usleep(100);
    }

    ir.write_file("test2");
    return NULL;
}

void Input_Recorder::write_file( const char * file_name ){
    std::cout << "writing file" << std::endl;
    const char* home_dir = std::getenv("HOME");
    if (home_dir == nullptr) {
        std::cerr << "Error: HOME environment variable not set." << std::endl;
        return;
    }

    // Create the full path for the file
    std::string file_path = std::string(home_dir) + "/" + file_name;
    std::cout << file_path << std::endl;
    // Open a binary file for writing
    std::ofstream outFile(file_path, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    // Write the vector to the binary file
    outFile.write(this->_record.buffer.data(), this->_record.buffer.size());
    // Close the file
    outFile.close();
    std::cout << "Data written to output.bin successfully." << std::endl;
    
}



