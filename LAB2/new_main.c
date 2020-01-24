#include <msp430.h>
#include <stdint.h>

#define FIFOSIZE 4

void registerTask(void * pTask, uint16_t priority);
void idleTask();
void BlinkLED_RED();
void BlinkLED_GREEN();
void startBRTOS();
void wait(uint16_t wait_ticks);
void fifoPUT(void * pTask, fifo_t * fifo) // Coloca no vetor de tasks
void *fifoGET(fifo_t * fifo)              // Retira do vetor de tasks e retorna a função
void WDT_ISR();

typedef struct{
    void (*pTask)();          // Entrada atual da tarefa
    uint16_t * pStack;        // Ponteiro da pilha
    uint16_t quantum, id, priority;
    volatile uint16_t wait_ticks;
}task_t;

typedef struct{
    uint16_t head, tail, size;
    task_t tasks[FIFOSIZE]; // Vetor para N tarefas na fila de execução
}fifo_t;

task_t tasks[10], currentTask; // vetor de tasks
fifo_t fifos[3];  // Vetor de filas de prioridade (0 - baixa, 1 - alta, 2 - blocked, pode-se ter N prioridades),

uint16_t taskCounter = 0;
uint16_t taskNumber = 0; // Tarefa atual que está sendo executada
void * schedSP = (void*)0x02500;

int main(void)
{
    // Inicializando variáveis
    // Prioridade Baixa
    fifos[0].head = 0;
    fifos[0].tail = 0;
    fifos[0].size = 0;
    // Prioridade Alta
    fifos[1].head = 0;
    fifos[1].tail = 0;
    fifos[1].size = 0;
    // Prioridade Bloqueada
    fifos[2].head = 0;
    fifos[2].tail = 0;
    fifos[2].size = 0;
    // Alocando memória para as tarefas
    registerTask(BlinkLED_RED, 1);
    registerTask(BlinkLED_GREEN,1);
    // Inicializando RTOS
    startBRTOS();
    // Inicio do watch dog
    while(1);

    return 0;
}


void registerTask(void * pTask, uint16_t priority){
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
    fifoPUT(tasks[taskCounter], &fifos[priority]);
    taskCounter++;

}

void idleTask()
{
    while(1);
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
    registerTask(idleTask, 0);

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

void fifoPUT(void pTask, fifo_t * fifo)
{
    fifo.task[fifo.tail] = ptask;
    fifo.tail++;
    fifo.size++;
    if(fifo.tail == FIFOSIZE)
        fifo.tail = 0;
}

task_t fifoGET(fifo_t * fifo)
{
  task_t task = fifo.task[fifo.head];
  fifo.head++;
  fifo.size--;
  if(fifo.head == FIFOSIZE){
      fifo.head = 0;
  }
  return task;
}

__attribute__((naked))
__attribute__((interrupt(WDT_VECTOR)))
void WDT_ISR(){
    //Executa uma tarefa e atualiza pTask. Função executada apenas em hardware, não se chama via software
    asm("pushm.a #12, R15" );    //Salva contexto
    asm("movx.a SP,   %0" : "=m" (tasks[taskNumber].pStack));
    asm("movx.a %0,   SP" :: "m" (schedSP));

    //taskNumber = (taskNumber + 1) % taskCounter;
    if(fifos[1].size > 0){ // Prioridade Alta
        currentTask = fifoGET(fifos[1]); // Desaloca primeiro o de maior prioridade
    }else //if(fifos[0].size > 0) // Prioridade baixa
        currentTask = fifoGET(fifos[0]); // Desaloca primeiro o de maior prioridade

    currentTask.wait_ticks--; // ATUALIZA OS TICKS DE TODAS AS TAREFAS PARA DAR O WAIT

    asm("movx.a SP,  %0" : "=m" (schedSP));
    asm("movx.a %0,  SP" :: "m" (currentTask.pStack)); // INVOCA A TAREFA
    asm("popm.a #12, R15");
    asm("RETI");
}
