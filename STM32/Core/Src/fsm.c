/*
 * fsm.c
 *
 *  Created on: Nov 3, 2025
 *      Author: Admin
 */

#include "fsm.h"

int MODE_CURRENT = 1;

static void turn_Off_LEDs(void) {
    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 |
                      GPIO_PIN_9 | GPIO_PIN_10,
                      SET);
    HAL_GPIO_WritePin(GPIOB,
                      GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  |
                      GPIO_PIN_4  | GPIO_PIN_5  | GPIO_PIN_6  | GPIO_PIN_7  |
                      GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 |
                      GPIO_PIN_12 | GPIO_PIN_13,
                      SET);
}

static void configure_and_display_mode(int mode, int timer_constant) {
    configure_leds(mode);
    show_mode(mode);
    show_time(timer_constant);
}

static void handle_mode() {
    switch (MODE_CURRENT) {
        case MODE_NORMAL:
            run_traffic_lights();
            break;
        case MODE_DO:
            configure_and_display_mode(MODE_DO, MOD_DO_TIMER);
            break;
        case MODE_VANG:
            configure_and_display_mode(MODE_VANG, MOD_VANG_TIMER);
            break;
        case MODE_XANH:
            configure_and_display_mode(MODE_XANH, MOD_XANH_TIMER);
            break;
        default:
            break;
    }
}

void execute_fsm() {
    handle_mode();
    if (check_MOD_1()) {
        MODE_CURRENT = (MODE_CURRENT % 4) + 1;
        turn_Off_LEDs();
        reset_to_defaults(MODE_CURRENT);
        reset_MOD_flags();
    }
    if (MODE_CURRENT != 1) {
        if (check_MOD_2()) {
            init_traffic_timers(MODE_CURRENT);
        }
    }
    if (check_MOD_3()) {
        apply_changes(MODE_CURRENT);
    }
}
