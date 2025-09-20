// #include "include/mouse.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/XKBlib.h>

#include "util/util.h"
#include "util/signal_handler/signal_handler.h"

#include <stdlib.h>
#include <stdio.h>
#include "include/kbm_io.h"
#include <sys/stat.h>//file status
#include <unistd.h>

#include "algorithm/random.h"


Window root, root_return, child_return;
int root_x, root_y, win_x, win_y;
unsigned int mask_return;
int old_button_state;
int poll_type;
XKeyEvent event;
Display *display;

static script_loop_callback_t script_loop_callback;


char keys[32]; // Array to hold the state of the keys
uint64_t old_keys[256];
static char key_map[256];
uint64_t cur_keys[256];


void input_monitor_init() __attribute__((constructor));
void input_monitor_destroy();

// bool* poll_keyboard();

void set_script_loop_callback(script_loop_callback_t callback ){
   script_loop_callback = callback;
}

void input_monitor_init(){
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
   atexit(input_monitor_destroy);

   for( int a  =0; a< 256; a++ ){
      event.keycode = a;
      KeySym keysym = XLookupKeysym(&event, 0);
      key_map[a] = keysym;
   }
}

void input_monitor_destroy(){
   XCloseDisplay(display);
}

void execute_event( event_log_t event_log ){
   usleep(event_log.wait);
   // printf("event: %d", event);
   switch (event_log.event) {
      case MOUSE_L_PRESS:
         XTestFakeButtonEvent(display, 1, True, CurrentTime);
         XSync(display, False);
         break;
      case MOUSE_L_RELEASE:
         XTestFakeButtonEvent(display, 1, False, CurrentTime);
         XSync(display, False);
         break;
      case MOUSE_MOVE:
         XTestFakeMotionEvent(display, DefaultScreen(display), event_log.x, event_log.y, 0);
         break;
      case KEY_PRESS:
         //// Get the keycode for 'h'
         // XKeysymToKeycode(display, XK_h);
    
         // // Simulate key press
         // XTestFakeKeyEvent(display, keycode, True, 0);
      
         // // Simulate key release
         // XTestFakeKeyEvent(display, keycode, False, 0);
         break;
      case KEY_RELEASE:
         //
         break;
      default:
         return;
   }

}


uint32_t poll_mouse(){
   XQueryPointer(display, root, &root_return, &child_return,\
               &root_x, &root_y, &win_x, &win_y, &mask_return);

   return mask_return;
}

uint32_t get_mouse_x(){
   poll_mouse();
   return root_x;
}

void * read_script(uint32_t* num_events, const char * file_path){
   FILE *file;

   char * script;

    // Determine the number of elements (this could be known beforehand)
    // For demonstration, let's assume we know it or read it from the file
    // Here, we will read the number of elements from the file
   struct stat st;
   stat(file_path, &st );
   *num_events = st.st_size / sizeof(event_log_t);

   // printf("num events: %lu\n", *num_events );
   // printf("num_bytes: %lu\n", st.st_size );
   // printf("path: %s\n", file_path);
   // printf("\nsize of event log: %lu", sizeof(event_log_t));
   // Open the binary file for reading
    file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("Failed to open file");
        return NULL;
    }

    // Allocate memory for the array of structs
    script = (char*)malloc( st.st_size );
   //  printf("malloc'd\n");
    if (script == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // Read the data into the array

      size_t readCount = fread(script, 1, sizeof(event_log_t)*(*num_events), file);
      printf("read count: %lu\n", readCount);
   //  if (readCount != num_events) {
   //      perror("Failed to read data");
   //      free(script);
   //      fclose(file);
   //      return -1;
   //  }

    fclose(file);
    return script;

}


off_t get_file_size( const char * file_name){
  struct stat st;
  stat(file_name, &st );
  return st.st_size;
}
int run_script( const char * file_path, kbm_io_t io ){
   
   event_log_t * events;
   uint32_t num_events;
   uint64_t start_read = get_time();
   events = read_script( &num_events, file_path);
   int x_pos = get_mouse_x();
   printf("time to read: %lu\n", get_time()-start_read);

   for( int a=0; a < num_events-4; a++ ){
      // printf("sleep: %u\n", events[a].wait);
      // printf("\n");
      if( should_exit () ) return -1;
      
      execute_event(events[a]);

      if( events[a].event == MOUSE_L_RELEASE ){
         if( get_mouse_x() != x_pos ){
            return -1;
         }

         if( io.click_delay ){
            if( io.click_delay_std_dev){
               double cur_delay = rand_normal(io.click_delay, io.click_delay_std_dev );
               XQueryKeymap(display, keys);
               usleep( cur_delay*1000000);
            }else{
               usleep(io.click_delay*1000000);
            }
            
         }

      }
   }
   free( events );
   return 0;

}


uint64_t* poll_keyboard(){
   XQueryKeymap(display,  keys);
   char k[32];
   for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 8; j++) {
             
            int keycode = (i * 8) + j;
            if (keys[i] & (1 << j)) {
                
                int keycode = (i * 8) + j;
                if( cur_keys[keycode] ){
                    continue;
                }else{
                    cur_keys[keycode] = get_time();
                }
                // Calculate the keycode
                event.keycode = keycode;
                
            }else if( cur_keys[keycode] ){
               event.keycode = keycode;
               char test=  XkbKeycodeToKeysym(display,keycode, 0,0);
               printf("key Released: %c\n", test);
               
               
               cur_keys[keycode] = 0;
            }
            
        }
    }
    return cur_keys;
}


