/**
 * @file signal_handler.c
 * @author Cory Barrett
 * @brief wrapper/reference for commonly used singal operations
 * @version 0.1
 * @date 2024-07-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H


// #include <csignal>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signal_handler.h"
#include <signal.h>

static volatile sig_atomic_t exit_flag = 0;
static sigset_t mask;

/**
 * @brief check if program should exit due to
 * signal interrupts.
 *
 * @return
 */
bool should_exit(){
  return exit_flag;
}

void set_exit_flag(bool flag){
  exit_flag = flag;
}

/**
 * @brief sets callback function for SIGINT, SIGTERM,
 * and SIGQUIT.
 *
 * @param func
 */
void interrupt_handler_init (void (*func)(int))
{
  establish_signal_handler(SIGINT, func);
  establish_signal_handler(SIGTERM, func);
  establish_signal_handler(SIGQUIT, func);
}


void establish_signal_handler (int sig, void (*func)(int))
{
    struct sigaction sig_action = {
        .sa_handler = func,
    };

    if (sigaction(sig, &sig_action, NULL) == -1)
    {
        perror("sigaction: set");
        exit(sig);
    }
}

/**
 * @brief Set the signal mask for signal blocking
 *
 * @param signal_mask
 */
void set_signal_mask( int32_t signal_mask ){
  sigemptyset(&mask);
  sigaddset(&mask, signal_mask );

  // This blocks all three, wiping out any existing mask in the kernel
  sigprocmask(SIG_SETMASK, &mask, NULL);
}

/**
 * @brief blocks all signals set in the set_signal_mask function.
 * useful for block interrupt signals durring critical tasks.
 *
 */
void block_signals(){
  sigprocmask(SIG_SETMASK, &mask, NULL);
}

/**
 * @brief unblocks all signals in the set_signal_mask function.
 * Used to allow signal interrupts to trigger
 *
 */
void unblock_signals(){
  sigprocmask(SIG_UNBLOCK, &mask, NULL);
}

/**
 * @brief Call this to unblock and then block the current blocked
 *        signals to alllow signals to trigger.
 *
 */
void check_signals(){
  sigprocmask(SIG_UNBLOCK, &mask, NULL);
  sigprocmask(SIG_SETMASK, &mask, NULL);
}



#endif
