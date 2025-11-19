/*
 * global.c
 *
 *  Created on: Nov 3, 2025
 *      Author: Admin
 */

#include "global.h"

#ifndef SCAN_INTERVAL_MS
#define SCAN_INTERVAL_MS 125
#endif

#ifndef LIGHT_STEP_MS
#define LIGHT_STEP_MS 400
#endif

int buf_mode[2] = {1, 2};
int buf_time[2] = {3, 4};

int DO_duration = 10;
int MOD_DO_TIMER = 10;
int DO_modified = 0;

int VANG_duration = 3;
int MOD_VANG_TIMER = 3;
int VANG_modified = 0;

int XANH_duration = 7;
int MOD_XANH_TIMER = 7;
int XANH_modified = 0;

int idx_mode = 0;
int idx_time = 2;

int direction = 1;

void show_7seg(int value, uint32_t pin) {
	if(value < 0 || value > 9)
		return;
	char seg_patterns[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
	for (int j = 0; j < 7; j++) {
		HAL_GPIO_WritePin(GPIOB, pin << j, (seg_patterns[value] >> j) & 1);
	}
}

void scan_7seg(int idx) {
	switch (idx) {
		case 0:
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			show_7seg(buf_mode[0], GPIO_PIN_0);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
			show_7seg(buf_mode[1], GPIO_PIN_0);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			show_7seg(buf_time[0], GPIO_PIN_7);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			show_7seg(buf_time[1], GPIO_PIN_7);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
}

void update_buffer_mode(int value) {
	if (value >= 0) {
		buf_mode[0] = value / 10;
		buf_mode[1] = value % 10;
	}
}

void update_buffer_time(int value) {
	if (value >= 0) {
		buf_time[0] = value / 10;
		buf_time[1] = value % 10;
	}
}

void show_mode(int value) {
	update_buffer_mode(value);
	if (tmr3_done == 1) {
		scan_7seg(idx_mode);
		idx_mode = (idx_mode + 1) % 2;
		init_tmr3(SCAN_INTERVAL_MS);
	}
}

void show_time(int value) {
	update_buffer_time(value);
	if (tmr4_done == 1) {
		scan_7seg(idx_time);
		idx_time++;
		if (idx_time > 3) {
			idx_time = 2;
		}
		init_tmr4(SCAN_INTERVAL_MS);
	}
}

void verify_timers() {
	if (DO_modified == 0) {
		MOD_DO_TIMER = DO_duration;
	} else {
		if (VANG_modified == 0) {
			MOD_VANG_TIMER = VANG_duration;
		} else {
			if (XANH_modified == 0) {
				MOD_XANH_TIMER = XANH_duration;
			}
		}
	}
	if (DO_modified == 1 || VANG_modified == 1 || XANH_modified == 1) {
		if (MOD_DO_TIMER == (MOD_VANG_TIMER + MOD_XANH_TIMER)) {
			DO_duration = MOD_DO_TIMER;
			VANG_duration = MOD_VANG_TIMER;
			XANH_duration = MOD_XANH_TIMER;
			DO_modified = 0;
			VANG_modified = 0;
			XANH_modified = 0;
		}
	}
}

void reset_to_defaults(int MODE_CURRENT) {
	switch (MODE_CURRENT) {
		case MODE_NORMAL:
			verify_timers();
			MOD_DO_TIMER = DO_duration;
			MOD_VANG_TIMER = VANG_duration;
			MOD_XANH_TIMER = XANH_duration;
			break;
		case MODE_DO:
			MOD_DO_TIMER = DO_duration;
			break;
		case MODE_VANG:
			MOD_VANG_TIMER = VANG_duration;
			break;
		case MODE_XANH:
			MOD_XANH_TIMER = XANH_duration;
			break;
		default:
			break;
	}
}

void init_traffic_timers(int MODE_CURRENT) {
	switch (MODE_CURRENT) {
		case MODE_DO:
			MOD_DO_TIMER = (MOD_DO_TIMER % 99) + 1;
			break;
		case MODE_VANG:
			MOD_VANG_TIMER = (MOD_VANG_TIMER % 99) + 1;
			break;
		case MODE_XANH:
			MOD_XANH_TIMER = (MOD_XANH_TIMER % 99) + 1;
			break;
		default:
			break;
	}
}

void configure_leds(int MODE_CURRENT) {
	if (tmr2_done == 1) {
		if (MODE_CURRENT == MODE_DO) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5|GPIO_PIN_8);
		} else if (MODE_CURRENT == MODE_VANG) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6|GPIO_PIN_9);
		} else if (MODE_CURRENT == MODE_XANH) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7|GPIO_PIN_10);
		}
		init_tmr2(250);
	}
}

static inline void config_north(GPIO_PinState r, GPIO_PinState y, GPIO_PinState g) {
    HAL_GPIO_WritePin(DO_N_GPIO_Port, DO_N_Pin, r);
    HAL_GPIO_WritePin(VANG_N_GPIO_Port, VANG_N_Pin, y);
    HAL_GPIO_WritePin(XANH_N_GPIO_Port, XANH_N_Pin, g);
}

static inline void config_south(GPIO_PinState r, GPIO_PinState y, GPIO_PinState g) {
    HAL_GPIO_WritePin(DO_D_GPIO_Port, DO_D_Pin, r);
    HAL_GPIO_WritePin(VANG_D_GPIO_Port, VANG_D_Pin, y);
    HAL_GPIO_WritePin(XANH_D_GPIO_Port, XANH_D_Pin, g);
}

void run_traffic_lights() {
    if (tmr1_done == 1) {
		if (direction == 1) {
			if (MOD_DO_TIMER > 0) {
				update_buffer_time(MOD_DO_TIMER);
				if (MOD_DO_TIMER > VANG_duration) {
					if (MOD_XANH_TIMER > 0) {
						config_north(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET);
						config_south(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET);
						update_buffer_mode(MOD_XANH_TIMER);
						MOD_XANH_TIMER -= 1;
					}
				} else {
					if (MOD_DO_TIMER <= VANG_duration && MOD_DO_TIMER >= 1) {
						if (MOD_VANG_TIMER > 0) {
							config_north(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET);
							config_south(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET);
							update_buffer_mode(MOD_VANG_TIMER);
							MOD_VANG_TIMER -= 1;
						}
					}
				}
				MOD_DO_TIMER -= 1;
			}
			if (MOD_VANG_TIMER == 0) {
				MOD_VANG_TIMER = VANG_duration;
			}
			if (MOD_XANH_TIMER == 0) {
				MOD_XANH_TIMER = XANH_duration;
			}
			if (MOD_DO_TIMER == 0) {
				MOD_DO_TIMER = DO_duration;
				direction = 2;
			}
		} else {
			if (MOD_DO_TIMER > 0) {
				update_buffer_mode(MOD_DO_TIMER);
				if (MOD_DO_TIMER > VANG_duration) {
					if (MOD_XANH_TIMER > 0) {
						config_south(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET);
						config_north(GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET);
						update_buffer_time(MOD_XANH_TIMER);
						MOD_XANH_TIMER -= 1;
					}
				} else {
					if (MOD_DO_TIMER <= VANG_duration && MOD_DO_TIMER >= 1) {
						if (MOD_VANG_TIMER > 0) {
							config_south(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET);
							config_north(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET);
							update_buffer_time(MOD_VANG_TIMER);
							MOD_VANG_TIMER -= 1;
						}
					}
				}
				MOD_DO_TIMER -= 1;
			}
			if (MOD_VANG_TIMER == 0) {
				MOD_VANG_TIMER = VANG_duration;
			}
			if (MOD_XANH_TIMER == 0) {
				MOD_XANH_TIMER = XANH_duration;
			}
			if (MOD_DO_TIMER == 0) {
				MOD_DO_TIMER = DO_duration;
				direction = 1;
			}
		}
		init_tmr1(LIGHT_STEP_MS);
	}
	if (tmr5_done == 1) {
		scan_7seg(idx_mode);
		idx_mode = (idx_mode + 1) % 2;
		scan_7seg(idx_time);
		idx_time++;
		if (idx_time > 3) idx_time = 2;
		init_tmr5(SCAN_INTERVAL_MS);
	}
}

void apply_changes(int MODE_CURRENT) {
	switch (MODE_CURRENT) {
		case MODE_DO:
			DO_modified = 1;
			break;
		case MODE_VANG:
			VANG_modified = 1;
			break;
		case MODE_XANH:
			XANH_modified = 1;
			break;
		default:
			break;
	}
}
