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
}

task_t fifoGet(fifo_t * f){
    increment(f->head);
    f->size--;
    return f->tasks[f->head];
}
