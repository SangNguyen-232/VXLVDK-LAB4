/*
 * software_timer.c
 *
 * Created on: Nov 3, 2025
 * Author: Admin
 */

#include "software_timer.h"

#ifndef TIMER_TICK_MS
#define TIMER_TICK_MS 10
#endif

int tmr1_done = 0;
static int tmr1_counter = 0;

int tmr2_done = 0;
static int tmr2_counter = 0;

int tmr3_done = 0;
static int tmr3_counter = 0;

int tmr4_done = 0;
static int tmr4_counter = 0;

int tmr5_done = 0;
static int tmr5_counter = 0;

void init_tmr5(int duration) {
    tmr5_counter = duration / TIMER_TICK_MS;
    tmr5_done = 0;
}

void init_tmr4(int duration) {
    tmr4_counter = duration / TIMER_TICK_MS;
    tmr4_done = 0;
}

void init_tmr3(int duration) {
    tmr3_counter = duration / TIMER_TICK_MS;
    tmr3_done = 0;
}

void init_tmr2(int duration) {
    tmr2_counter = duration / TIMER_TICK_MS;
    tmr2_done = 0;
}

void init_tmr1(int duration) {
    tmr1_counter = duration / TIMER_TICK_MS;
    tmr1_done = 0;
}

static inline void decrementTimer(int *counter, int *flag) {
    if (*counter > 0) {
        (*counter)--;
        if (*counter <= 0) {
            *flag = 1;
        }
    }
}

void process_timers(void) {
    decrementTimer(&tmr5_counter, &tmr5_done);
    decrementTimer(&tmr4_counter, &tmr4_done);
    decrementTimer(&tmr3_counter, &tmr3_done);
    decrementTimer(&tmr2_counter, &tmr2_done);
    decrementTimer(&tmr1_counter, &tmr1_done);
}
