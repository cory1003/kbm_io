
#include <cstdint>
#include <iostream>
#include <pthread.h>
#include "include/input_record.h"
#include <getopt.h>
#include <sys/types.h>
#include <iomanip>

extern "C" {
   #include "util/util.h"
   #include "util/signal_handler/signal_handler.h"
   #include "include/kbm_io.h"
//    #include "util/algorithm/random.h"
}
#include <getopt.h>

void sigint_handler(int sig){
    std::cout << "exiting..\n";
    set_exit_flag( true );
}

enum app_mode { PLAY, RECORD };



kbm_io_t io = {0};

typedef struct {
    struct option opt;
    const char * description;
} arg_struct_t;

static arg_struct_t arguments[]= {
    

    {"help", optional_argument, NULL, 'h', ""},
    {"script", optional_argument, NULL, 's', ""},
    {"record", optional_argument, NULL, 'r', ""},
    {"play", optional_argument, NULL, 'p', ""},
        {"delayScipt", required_argument, NULL, 'D', "Msec to delay before starting script."},
        {"delayClick", optional_argument, NULL, 'd', ""},
    {"StandardDev", optional_argument, NULL, 'S', ""},
    {"Iterations", optional_argument, NULL, 'i', ""},
    {"ClickOnly", optional_argument, NULL, 'C', ""},
    {NULL, 0, NULL, 0, ""}
};

void get_long_options(){

}

void delay_click( std::string script_file_path, double mean, double deviation );

void help(){
    std::cout << "Usage: auto-click [OPTIONS]\n";
    std::cout << "Example: auto-click -S .1 -p -d 1.0 -i 2 -D 1.5";
    std::cout << "Options:\n";
    int num_options = sizeof(arguments)/sizeof(arg_struct_t) - 1;
    for(int i = 0; i < num_options; i++ ){
        std::cout << "    -" <<  char(arguments[i].opt.val) << std::left << std::setw(20) << std::string("    --") + std::string(arguments[i].opt.name) << "   " << arguments[i].description << std::endl;
    }
}

int main(int argc, char *argv[]) {


    io.num_iterations = 1000;
    io.click_delay = 0;
    io.click_delay_std_dev= 0;
    double script_delay;


    interrupt_handler_init(sigint_handler);
    int opt;
    int option_index = 0;
    // int verbose = 0;

    struct option l_opts[sizeof(arguments)/sizeof(arg_struct_t)];
    for( int a =0; a< sizeof(arguments)/sizeof(arg_struct_t); a++){
        l_opts[a] = arguments[a].opt;
    }


    uint32_t mode = -1;
    // required:optional
    while( (opt = getopt_long(argc, argv, "hs:rpD:d:S:i:C", l_opts, &option_index)) != -1) {
        switch (opt) {
            default:
                break;
            case 'h':
                help();
                break;
            case 's':
                snprintf(io.script_name, sizeof(io.script_name), "%s", optarg);
                break;
            case 'r':
                mode = RECORD;
                break;
            case 'p':
                mode = PLAY;
                break;
            case 'd':
                sscanf(optarg, "%lf", &io.click_delay);
                std::cout << "d " << io.click_delay << std::endl;
                break;
            case 'D':
                script_delay = std::stod(optarg);
                if( script_delay> 0){
                    if( !(script_delay > 0.1 ) ){
                        uint64_t start_time = get_time();
                        while( get_time() < script_delay + start_time )
                        usleep(script_delay*1000000);
                    } else{ 
                        uint64_t start_time = get_time();
                        while( get_time() < script_delay + start_time ){
                            usleep(10*1000);
                        }
                    }
                }
                break;
            case 'S':
                io.click_delay_std_dev = std::stod(optarg);
                break;
            case 'i':
                io.num_iterations = atoi(optarg);
                std::cout << "Number of Iterations: " << io.num_iterations << std::endl;
                break;
            case 'C':
                io.click_only = true;
                break;
        }
    }
    
    if( mode == PLAY ){
        auto time = get_time();
        int num_loops = 0;
        // while( (get_time() - time)/1000000.0/60.0 < 145.0 ){
        uint32_t count = 0;
        while( count < io.num_iterations ){

            if (run_script("/home/doug/test", io ) == -1 ) break;
            printf("loop: %d\n", ++num_loops);
            count++;
        }
        // run_script("/home/doug/test");
        std::cout << (get_time() - time )/1000000.0 << std::endl;
        return 0;
    } else if( mode == RECORD ){
        while( !should_exit() ){
            pthread_t thread; // Thread identifier
            int threadId = 1; // Thread argument
    
            // Create a new thread that runs threadFunction
            if (pthread_create(&thread, NULL, io_record, &io) != 0) {
                perror("Failed to create thread");
                return 1;
            }
            
            // Wait for the thread to finish
            if (pthread_join(thread, NULL) != 0) {
                perror("Failed to join thread");
            }
            
            std::cout << "thread joined.\n"; 
            usleep(1000);
        } 
        std::cout << "exiting\n"; 
        return 0;
    }{
        // delay_click( app.script_name, app.delay, app.standard_deviation);
    }
    

    

}


void delay_click( std::string script_file_path, double mean, double deviation ){

}