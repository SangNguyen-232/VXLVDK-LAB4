/*
 * button.h
 *
 *  Created on: Nov 3, 2025
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#ifndef NORMAL_STATE
#define NORMAL_STATE GPIO_PIN_SET
#endif
#ifndef ACTIVE_STATE
#define ACTIVE_STATE GPIO_PIN_RESET
#endif

extern int MOD_1_ACTIVE;
int check_MOD_1();

extern int MOD_2_ACTIVE;
int check_MOD_2();

extern int MOD_3_ACTIVE;
int check_MOD_3();

int check_MOD_1_long();
void reset_MOD_flags();
void process_input();

#endif /* INC_BUTTON_H_ */
