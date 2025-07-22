/**
 * @file signal_handler.h
 * @author Cory Barrett
 * @brief wrapper/reference for commonly used singal operations
 * @version 0.1
 * @date 2024-07-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <stdbool.h>


bool should_exit ();
void set_exit_flag (bool flag);
void interrupt_handler_init ( void (*func)(int));
void establish_signal_handler (int sig, void (*func)(int));
void block_intterupts ();
void check_signals ();
