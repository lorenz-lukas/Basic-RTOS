#include <msp430.h>
#include <stdint.h>


/**
 * main.c
 */

typedef struct{
    void (*pTask)();          // Entrada atual da tarefa
    uint16_t * pStack;         // Ponteiro da pilha
    volatile uint16_t wait_ticks;
}task_t;


typedef struct{
    uint16_t head;
    uint16_t tail;
    uint16_t size;
}fifo_t;



task_t tasks[10]; // vetor de tasks
fifo_t fifos[2]; // Vetor de filas de prioridade

uint16_t taskCounter = 0;
uint16_t taskNumber = 0; // Tarefa atual que está sendo executada
void * schedSP = (void*)0x02500;

void registerTask();
void BlinkLED_RED();
void BlinkLED_GREEN();
void startBRTOS();
void wait();
void WDT_ISR();

int main(void)
{
    registerTask(BlinkLED_RED);
    registerTask(BlinkLED_GREEN);

    startBRTOS();

    while(1);

    return 0;
}


void registerTask(void * pTask){
    tasks[taskCounter].pTask = pTask;
    tasks[taskCounter].pStack = (uint16_t *)0x2800 + 0x80*(taskCounter);

    tasks[taskCounter].pStack--;
    *(tasks[taskCounter].pStack) = (uint16_t)pTask;

    tasks[taskCounter].pStack--;
    *(tasks[taskCounter].pStack) = ((uint32_t)pTask >> 4) & 0xF000;
    *(tasks[taskCounter].pStack) |= GIE;                         // GIE = SR

    for(int a = 0; a < 24; a ++){                          // Preenche o resto da pilha com '0'
        tasks[taskCounter].pStack--;
        *(tasks[taskCounter].pStack) = 0;
    }

    taskCounter++;

}

void BlinkLED_RED(){
    P1DIR |= BIT0;
    while(1){
          wait(250);
          P1OUT ^= BIT0;
      }
}

void BlinkLED_GREEN(){
    P4DIR |= BIT7;
    while(1){
        wait(250);
        P4OUT ^= BIT7;
      }
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

    // Inicializando a primeira tarefa
    asm("movx.a  %0, SP" :: "m" (tasks[0].pStack));
    asm("pushx.a %0" :: "m" (tasks[0].pTask));
}

void wait(uint16_t wait_ticks)
{
    tasks[taskNumber].wait_ticks = wait_ticks;
    while(tasks[taskNumber].wait_ticks);
}

__attribute__((naked))
__attribute__((interrupt(WDT_VECTOR)))
void WDT_ISR(){
    //Executa uma tarefa e atualiza pTask. Função executada apenas em hardware, não se chama via software
    asm("pushm.a #12, R15" );    //Salva contexto
    asm("movx.a SP,   %0" : "=m" (tasks[taskNumber].pStack));
    asm("movx.a %0,   SP" :: "m" (schedSP));

    taskNumber = (taskNumber + 1) % taskCounter;

    for(int i=0;i<taskNumber; i++)tasks[].wait_ticks--; // ATUALIZA OS TICKS DE TODAS AS TAREFAS PARA DAR O WAIT

    asm("movx.a SP,  %0" : "=m" (schedSP));
    asm("movx.a %0,  SP" :: "m" (tasks[taskNumber].pStack)); // INVOCA A TAREFA
    asm("popm.a #12, R15");
    asm("RETI");
}
