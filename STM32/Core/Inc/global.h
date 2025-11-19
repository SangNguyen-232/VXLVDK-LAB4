/*
 * global.h
 *
 *  Created on: Nov 3, 2025
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "button.h"

#define MODE_NORMAL	1
#define MODE_DO	    2
#define MODE_VANG	3
#define MODE_XANH   4

extern int MOD_DO_TIMER;
extern int DO_duration;

extern int MOD_VANG_TIMER;
extern int VANG_duration;

extern int MOD_XANH_TIMER;
extern int XANH_duration;

void apply_changes(int MODE_CURRENT);
void init_traffic_timers(int MODE_CURRENT);
void reset_to_defaults(int MODE_CURRENT);
void run_traffic_lights(void);
void configure_leds(int MODE_CURRENT);
void show_7seg(int value, uint32_t pin);
void show_mode(int value);
void update_buffer_mode(int value);
void update_buffer_time(int value);
void scan_7seg(int idx);
void show_time(int value);
void verify_timers(void);

#endif /* INC_GLOBAL_H_ */
