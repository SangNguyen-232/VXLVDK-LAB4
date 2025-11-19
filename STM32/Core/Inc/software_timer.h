/*
 * software_timer.h
 *
 *  Created on: Nov 3, 2025
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

#ifndef TIMER_TICK_MS
#define TIMER_TICK_MS 10
#endif

extern int tmr1_done;
void init_tmr1(int duration);

extern int tmr2_done;
void init_tmr2(int duration);

extern int tmr3_done;
void init_tmr3(int duration);

extern int tmr4_done;
void init_tmr4(int duration);

extern int tmr5_done;
void init_tmr5(int duration);

void process_timers(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
