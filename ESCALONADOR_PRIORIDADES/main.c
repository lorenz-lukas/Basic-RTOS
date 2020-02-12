#include <msp430.h>
#include <stdint.h>
#include "kernel.h"



/**
 * main.c
 */
void BlinkLED_RED();
void BlinkLED_GREEN();


int main(void){
    registerTask(BlinkLED_RED,   PRIORITY_MAX, 1);
    registerTask(BlinkLED_GREEN, PRIORITY_MAX, 1);

    startBRTOS();
}



void BlinkLED_RED(){
    P1DIR |= BIT0;
    while(1){
        P1OUT ^= BIT0;
        wait(500);
    }
}

void BlinkLED_GREEN(){
    P4DIR |= BIT7;
    while(1){
        P4OUT ^= BIT7;
        wait(250);
    }
}
