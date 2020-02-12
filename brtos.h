#include <msp430.h>
#include <stdint.h>

typedef struct{
    void (*pTask)();          // Entrada atual da tarefa
    uint16_t * pStack;         // Ponteiro da pilha

}task_t;

task_t tasks[10];

void startBRTOS();
void WDT_ISR();
