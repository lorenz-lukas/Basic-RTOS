#include <msp430.h> 
#include <stdint.h>


/**
 * main.c
 */

typedef struct{
    void (*pTask)();          // Entrada atual da tarefa
    uint16_t * pStack;         // Ponteiro da pilha

}task_t;

task_t tasks[10];
uint16_t taskCounter = 0;
uint16_t taskNumber = 0;
void * schedSP = (void*)0x02500;


void registerTask(void * pTask){
    tasks[taskCounter].pTask = pTask;
    tasks[taskCounter].pStack = (uint16_t *)0x2800 + 0x80*(taskCounter);

    tasks[taskCounter].pStack--;
    *(tasks[taskCounter].pStack) = (uint16_t)pTask;

    tasks[taskCounter].pStack--;
    *(tasks[taskCounter].pStack) = ((uint32_t)pTask >> 4) & 0xF000;
    *(tasks[taskCounter].pStack) |= GIE;                         // GIE = SR


    // tasks[taskCounter].pStack--;
    //*(tasks[taskCounter].pStack) |= 0x008;
    //*(tasks[taskCounter].pStack) = (&pTask >> 4) & 0xF000|0X008; //0x008 = SR value

    //tasks[taskCounter].pStack--;

    for(int a = 0; a < 24; a ++){                          // Preenche o resto da pilha com '0'
        tasks[taskCounter].pStack--;
        *(tasks[taskCounter].pStack) = 0;
    }

    taskCounter++;
}

void BlinkLED_RED(){


    P1DIR |= BIT0;

    while(1){
        volatile uint16_t i = 50000;
        while(i--);

        P1OUT ^= BIT0;
    }
}

void BlinkLED_GREEN(){

    P4DIR |= BIT7;

    while(1){
        volatile uint16_t i = 25000;
        while(i--);

        P4OUT ^= BIT7;
    }
}

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

int main(void)
{

    registerTask(BlinkLED_RED);
    registerTask(BlinkLED_GREEN);

    startBRTOS();

    while(1);


    return 0;
}

__attribute__((naked))
__attribute__((interrupt(WDT_VECTOR)))

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

