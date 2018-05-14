#include "./queue.h"
#include <stdbool.h> // bools
#include <stdio.h>   // perror
#include <stdlib.h>  // free, realloc, size_t
#include <string.h>  // memcpy

struct Queue {
	void **data_;
	size_t capacity_;
	size_t size_;
	size_t head_;
	size_t tail_;
};

/*
 * Function: queueNew
 * return new queue struct
 * ------------------------------
 *  @param d: size of data to be held
 *  returns: new initialized queue
 */

struct Queue *
queueNew(size_t d)
{
	struct Queue *ret_q = malloc(sizeof(struct Queue));

	ret_q->data_     = NULL;
	ret_q->capacity_ = 0;
	ret_q->size_     = 0;
	ret_q->head_     = 0;
	ret_q->tail_     = 0;

	return ret_q;
}
