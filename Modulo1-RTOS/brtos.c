#include "brtos.h"

void startBRTOS(){
    WDTCTL = WDTSSEL__ACLK |    // ACLK
            WDTTMSEL |          // Intervalo
            WDTIS_5 |           // Time interval select
            WDTPW;              // Password;

    SFRIE1 |= WDTIE;           // Interrupção watchdog_timer
    __enable_interrupt();
    tasks[0].pStack += 26;

    asm("movx.a %0,SP" :: "m" (tasks[0].pStack));
    asm("pushx.a %0" :: "m" (tasks[0].pTask));
}

void WDT_ISR(){
    //Executa uma tarefa e atualiza pTask
    asm("pushm.a #12,R15" );    //Salva contexto
    asm("movx.a SP, %0" : "=m" (tasks[taskNumber].pStack));
    asm("movx.a %0,SP" :: "m" (schedSP));

    taskNumber = (taskNumber + 1) % taskCounter;

    asm("movx.a SP,%0" : "=m" (schedSP));
    asm("movx.a %0,SP" :: "m" (tasks[taskNumber].pStack));
    asm("popm.a #12,R15");
    asm("RETI");
}
