/*****************************************************************************
*                                                                            *
*  ------------------------------- queue.c --------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>

#include "integer_list.h"
#include "integer_queue.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------ queue_init ------------------------------  *
*                                                                            *
*****************************************************************************/

void integer_queue_init (integer_queue_t* queue) {
  integer_list_init (queue);
}

/*****************************************************************************
*                                                                            *
*  ------------------------------ queue_destroy----------------------------  *
*                                                                            *
*****************************************************************************/

void integer_queue_destroy (integer_queue_t *queue) {
  integer_list_destroy (queue);
}

/*****************************************************************************
*                                                                            *
*  ------------------------------ queue_size ------------------------------  *
*                                                                            *
*****************************************************************************/

int integer_queue_size (integer_queue_t * queue) {
  return integer_list_size (queue);
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- queue_enqueue ----------------------------  *
*                                                                            *
*****************************************************************************/

int integer_queue_enqueue(integer_queue_t *queue, int data) {
  /*  Enqueue the data.  */
  return integer_list_ins_next(queue, integer_list_tail(queue), data);
}

/*****************************************************************************
*                                                                            *
*  ----------------------------- queue_dequeue ----------------------------  *
*                                                                            *
*****************************************************************************/

/* User has to check that the queue is not empty */
int integer_queue_dequeue(integer_queue_t* queue, int* data) {
  /*  Dequeue the data.  */
  return integer_list_rem_next(queue, NULL, data);
}

/*****************************************************************************
*                                                                            *
*  ------------------------------ queue_peek ------------------------------  *
*                                                                            *
*****************************************************************************/

/* User has to check that the queue is not empty */
int integer_queue_peek(integer_queue_t * queue) {
    return queue->head->data;
}
