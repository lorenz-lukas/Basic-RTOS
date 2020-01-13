#include <msp430.h> 
#include <stdint.h>


/**
 * main.c
 */

typedef struct{
    uint16_t * pTask;          // Entrada atual da tarefa
    uint16_t * pStack;         // Ponteiro da pilha

}task_t;

task_t tasks[10];
uint16_t taskCounter = 0;


void registerTask(void *i){
    tasks[taskCounter].pTask = i;
    tasks[taskCounter].pStack = 0x2800 + 0x100*(taskCounter);

    tasks[taskCounter].pStack--;
    *(tasks[taskCounter].pStack) = GIE;                         // GIE = SR

    tasks[taskCounter].pStack--;
    *(tasks[taskCounter].pStack) = i;

    tasks[taskCounter].pStack--;
    *(tasks[taskCounter].pStack) = (i >> 4) & 0xF000|0X008; //0x008 = SR value

    tasks[taskCounter].pStack--;

    for(int a = 0; a < 12; a ++){                          // Preenche o resto da pilha com '0'
        tasks[taskCounter].pStack--;
        *(tasks[taskCounter].pStack) = 0;
    }

    taskCounter++;
}

int main(void)
{


    WDTCTL = WDTSSEL__ACLK |    // ACLK
            WDTTMSEL |          // Intervalo
            WDTIS_4 |           // Time interval select
            WDTPW;              // Password;


    SFRIE1 |= WDTIE;           // Interrupção watchdog_timer
    __enable_interrupt();


    while(1);

    return 0;
}

__attribute__((interrupt(WDT_VECTOR)))
void WDT_ISR(){
    //Executa uma tarefa e atualiza pTask


}

