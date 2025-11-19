/*
 * sche.c
 *
 *  Created on: Nov 18, 2025
 *      Author: Admin
 */

#include "sche.h"

#include <stddef.h>
#include <string.h>

static sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void) {
    memset(SCH_tasks_G, 0, sizeof(SCH_tasks_G));
}

uint32_t SCH_Add_Task(TaskFunction pFunction, uint32_t DELAY, uint32_t PERIOD) {
    for (uint32_t i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].pTask == NULL) {
            SCH_tasks_G[i].pTask = pFunction;
            SCH_tasks_G[i].Delay = DELAY;
            SCH_tasks_G[i].Period = PERIOD;
            SCH_tasks_G[i].RunMe = 0;
            return i;
        }
    }
    return SCH_INVALID_TASK;
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
    if (taskID >= SCH_MAX_TASKS) {
        return 0;
    }
    SCH_tasks_G[taskID].pTask = NULL;
    SCH_tasks_G[taskID].Delay = 0;
    SCH_tasks_G[taskID].Period = 0;
    SCH_tasks_G[taskID].RunMe = 0;
    return 1;
}
// Độ phức tạp là O(n)
//void SCH_Update(void) {
//    for (int i = 0; i < SCH_MAX_TASKS; i++) {
//        if (SCH_tasks_G[i].pTask != NULL) {
//            if (SCH_tasks_G[i].Delay == 0) {
//                SCH_tasks_G[i].RunMe += 1;
//                if (SCH_tasks_G[i].Period != 0) {
//                    SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
//                }
//            } else {
//                SCH_tasks_G[i].Delay -= 1;
//            }
//        }
//    }
//}

// Độ phức tạp là O(1)
void SCH_Update(void) {
    static uint32_t currentIndex = 0;
    if (SCH_tasks_G[currentIndex].pTask != NULL) {
        if (SCH_tasks_G[currentIndex].Delay == 0) {
            SCH_tasks_G[currentIndex].RunMe += 1;
            if (SCH_tasks_G[currentIndex].Period != 0) {
                SCH_tasks_G[currentIndex].Delay = SCH_tasks_G[currentIndex].Period;
            }
        } else {
            SCH_tasks_G[currentIndex].Delay -= 1;
        }
    }
    currentIndex = (currentIndex + 1) % SCH_MAX_TASKS;
}

void SCH_Dispatch_Tasks(void) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].RunMe > 0 && SCH_tasks_G[i].pTask != NULL) {
            (*SCH_tasks_G[i].pTask)();
            SCH_tasks_G[i].RunMe -= 1;
            if (SCH_tasks_G[i].Period == 0) {
                SCH_Delete_Task(i);
            }
        }
    }
}




