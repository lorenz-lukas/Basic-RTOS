#include <msp430.h>
#include <stdint.h>
#include "kernel.h"



/**
 * main.c
 */
void BlinkLED_RED();
void BlinkLED_GREEN();


int main(void){
    registerTask(BlinkLED_RED,PRIORITY_MAX, 3);
    registerTask(BlinkLED_GREEN, PRIORITY_MAX, 1);

    startBRTOS();

    while(1);

    return 0;
}



void BlinkLED_RED(){
    P1DIR |= BIT0;
    while(1){
        wait(500);
        P1OUT ^= BIT0;
    }
}

void BlinkLED_GREEN(){
    P4DIR |= BIT7;
    while(1){
        wait(1000);
        P4OUT ^= BIT7;
    }
}
