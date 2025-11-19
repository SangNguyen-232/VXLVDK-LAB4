/*
 * sche.h
 *
 *  Created on: Nov 18, 2025
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

#ifndef SCH_MAX_TASKS
#define SCH_MAX_TASKS 8
#endif

typedef void (*TaskFunction)(void);

typedef struct {
    TaskFunction pTask;
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
} sTask;

#define SCH_INVALID_TASK 0xFFFFFFFFu

void SCH_Init(void);
uint32_t SCH_Add_Task(TaskFunction pFunction, uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);

#endif /* INC_SCHE_H_ */
