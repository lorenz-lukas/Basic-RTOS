/*
 * kernel.c
 *
 *  Created on: 27 de jan de 2020
 *      Author: igorsantos e lorenz-lukas
 */

#include "kernel.h"
#include "fifo.h"


fifo_t fifo[PRIORITY_MAX+2];

uint16_t taskCounter = 0;
uint16_t taskNumber = 0; // Tarefa atual que está sendo executada
task_t runningTask;
uint16_t currentQuantum = 0;

void * schedSP = (void*)0x02500;

void idleTask()
{
    while(1);
}

void registerTask(void * pTask, uint16_t priority, uint16_t quantum){

    task_t t;

    t.pTask = pTask;
    t.pStack = (uint16_t *)0x2800 + 0x80*(taskCounter);

    t.pStack--;
    *(t.pStack) = (uint16_t)pTask;

    t.pStack--;
    *(t.pStack) = ((uint32_t)pTask >> 4) & 0xF000;
    *(t.pStack) |= GIE;                         // GIE = SR

    for(int a = 0; a < 24; a ++){                          // Preenche o resto da pilha com '0'
        t.pStack--;
        *(t.pStack) = 0;
    }

    t.priority = priority;
    t.wait_ticks = 0;
    t.quantum = quantum;
    if(fifo[priority].size < FIFOMAXSIZE){
        fifoPut(&fifo[priority],t);
    }

    taskCounter++;

}

void startBRTOS()
{

    registerTask(idleTask, PRIORITY_LOW, 1);

    WDTCTL = WDTSSEL__ACLK |    // ACLK
            WDTTMSEL |          // Intervalo
            WDTIS_7 |           // Time interval select
            WDTPW |              // Password;
            WDTCNTCL;

    SFRIE1 |= WDTIE;           // Interrupção watchdog_timer
    __enable_interrupt();

    for(uint8_t i = PRIORITY_MAX; i != PRIORITY_LOW; i--)
    {
        if(fifo[i].size != 0)
        {
            runningTask = fifoGet(&fifo[i]);
            break;
        }
    }

    currentQuantum = runningTask.quantum;

    runningTask.pStack += 26;

    // Inicializando a primeira tarefa
    asm("movx.a  %0, SP" :: "m" (runningTask.pStack));
    asm("pushx.a %0" :: "m" (runningTask.pTask));
    asm("RETA");
}


__attribute__((naked))
__attribute__((interrupt(WDT_VECTOR)))
void WDT_ISR()
{
    //save context
    asm("pushm.a #12,R15");
    //save task
    asm("movx.a SP,%0" : "=m" (runningTask.pStack));

    //asm("movx.a %0,SP" :: "m" (schedSP));

    //taskNumber = (taskNumber  + 1) % nRegTasks;
    scheduler();
    //asm("movx.a SP,%0" : "=m" (schedSP));

    asm("movx.a %0,SP" :: "m" (runningTask.pStack));
    asm("popm.a #12, R15");
    asm("RETI");
}

void wait(uint16_t wait_ticks)
{
    //fifoPUT(currentTask, &fifos[3]);

    runningTask.wait_ticks = wait_ticks;
    while(runningTask.wait_ticks);
}

void scheduler(){


    if(runningTask.wait_ticks){
        fifoPut(&fifo[BLOCKED_FIFO], runningTask);
    }

    task_t t;

    for(uint16_t j = PRIORITY_MAX; j < PRIORITY_LOW; j-- )
    {
        t = fifoGet(&fifo[j]);
        t.wait_ticks--;
        fifoPut(&fifo[j], t);
     }

    if(--currentQuantum!=0){
      //  runningTask.wait_ticks=10;
        return;
    }


    for(uint8_t p = PRIORITY_MAX; p > PRIORITY_LOW; p--){
        if(fifo[p].size != 0){
            runningTask = fifoGet(&fifo[p]);
            currentQuantum = runningTask.quantum;
            return;
        }
    }
}
