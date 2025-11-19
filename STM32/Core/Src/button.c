/*
 * button.c
 *
 *  Created on: Nov 3, 2025
 *      Author: Admin
 */

#include "button.h"
#include "software_timer.h"

#ifndef AUTO_REPEAT_MS
#define AUTO_REPEAT_MS 100
#endif

static int Tmp_0 = NORMAL_STATE;
static int Tmp_1 = NORMAL_STATE;
static int Tmp_2 = NORMAL_STATE;
static int Tmp_3 = NORMAL_STATE;

static int MOD_1_state = NORMAL_STATE;
int MOD_1_ACTIVE = 0;

static int MOD_2_state = NORMAL_STATE;
int MOD_2_ACTIVE = 0;

static int MOD_3_state = NORMAL_STATE;
int MOD_3_ACTIVE = 0;

static int KeyTimeout = AUTO_REPEAT_MS / TIMER_TICK_MS;
static int MOD_1_long = 0;

int check_MOD_1() {
    if (MOD_1_ACTIVE) {
        MOD_1_ACTIVE = 0;
        return 1;
    }
    return 0;
}

int check_MOD_2() {
    if (MOD_2_ACTIVE) {
        MOD_2_ACTIVE = 0;
        return 1;
    }
    return 0;
}

int check_MOD_3() {
    if (MOD_3_ACTIVE) {
        MOD_3_ACTIVE = 0;
        return 1;
    }
    return 0;
}

int check_MOD_1_long() {
    if (MOD_1_long) {
        MOD_1_long = 0;
        return 1;
    }
    return 0;
}

void reset_MOD_flags() {
    MOD_1_ACTIVE = 0;
    MOD_2_ACTIVE = 0;
    MOD_3_ACTIVE = 0;
}

static void sample_inputs(void) {
    Tmp_2 = Tmp_1;
    Tmp_1 = Tmp_0;
    MOD_1_state = HAL_GPIO_ReadPin(MOD_1_GPIO_Port, MOD_1_Pin);
    MOD_2_state = HAL_GPIO_ReadPin(MOD_2_GPIO_Port, MOD_2_Pin);
    MOD_3_state = HAL_GPIO_ReadPin(MOD_3_GPIO_Port, MOD_3_Pin);
    Tmp_0 = MOD_1_state && MOD_2_state && MOD_3_state;
}

static void set_active_for_current_mod(void) {
    if (MOD_1_state == ACTIVE_STATE) {
        MOD_1_ACTIVE = 1;
    } else if (MOD_2_state == ACTIVE_STATE) {
        MOD_2_ACTIVE = 1;
    } else if (MOD_3_state == ACTIVE_STATE) {
        MOD_3_ACTIVE = 1;
    }
}

void process_input() {
    sample_inputs();
    if ((Tmp_1 == Tmp_0) && (Tmp_1 == Tmp_2)) {
        if (Tmp_2 != Tmp_3) {
            Tmp_3 = Tmp_2;
            if (Tmp_3 == ACTIVE_STATE) {
                KeyTimeout = AUTO_REPEAT_MS;
                set_active_for_current_mod();
            }
        } else {
            KeyTimeout--;
            if (KeyTimeout == 0) {
                KeyTimeout = AUTO_REPEAT_MS;
                if (Tmp_3 == ACTIVE_STATE) {
                    set_active_for_current_mod();
                }
            }
        }
    }
}
