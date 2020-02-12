/*
 * fifo.h
 *
 *  Created on: 27 de jan de 2020
 *      Author: igorsantos e lorenz-lukas
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdint.h>
#include "kernel.h"

#define FIFOMAXSIZE 3
#define increment(x) x = (x+1) % FIFOMAXSIZE

#define SUCESS  0
#define ERROR_FIFO_FULL -1
#define ERROR_FIFO_EMPTY -2

typedef struct  {
    uint8_t head, tail, size;
    task_t    tasks[FIFOMAXSIZE];
}fifo_t;

void fifoPut(fifo_t *, task_t);
task_t fifoGet(fifo_t *);



#endif /* FIFO_H_ */
