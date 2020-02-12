/*
 * kernel.h
 *
 *  Created on: 27 de jan de 2020
 *      Author: igorsantos e lorenz-lukas
 */
#include <msp430.h>
#include <stdint.h>
#include "fifo.h"


#ifndef KERNEL_H_
#define KERNEL_H_


#define BLOCKED_FIFO  2
#define PRIORITY_MAX  1
#define PRIORITY_LOW  0

typedef struct{
    void (*pTask)();          // Entrada atual da tarefa
    uint16_t * pStack;         // Ponteiro da pilha
    volatile uint16_t wait_ticks;
    uint8_t         priority;
    //uint16_t         finished;
    uint8_t         quantum;
}task_t;

void registerTask(void *, uint8_t, uint8_t);
void startBRTOS();
void wait(volatile uint16_t);
void updateBlockedQueue();
void scheduler();
void idle();
void WDT_ISR();
void backgroundTaskFunction();


#endif /* KERNEL_H_ */
