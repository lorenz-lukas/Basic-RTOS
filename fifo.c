/*
 * fifo.c
 *
 *  Created on: 27 de jan de 2020
 *      Author: igorsantos e lorenz-lukas
 */

#include <stdint.h>
#include "fifo.h"


void fifoPut(fifo_t * f, task_t t){
    increment(f->tail);
    f->size++;
    f->tasks[f->tail] = t;
    if(f->tail == FIFOMAXSIZE)
        f->tail = 0;
}

task_t fifoGet(fifo_t * f){
    increment(f->head);
    f->size--;
    if(f->head == FIFOMAXSIZE){
        f->head = 0;
    }
    return f->tasks[f->head];
}
