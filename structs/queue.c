#include "./queue.h"
#include <stdbool.h> // bools
#include <stdio.h>   // perror
#include <stdlib.h>  // free, realloc, size_t
#include <string.h>  // memcpy

struct Queue {
	void **data_;
	size_t data_size_;
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

	ret_q->data_      = NULL;
	ret_q->data_size_ = d;
	ret_q->capacity_  = 0;
	ret_q->size_      = 0;
	ret_q->head_      = 0;
	ret_q->tail_      = 0;

	return ret_q;
}

/*
 * Function: Queue_resize_
 * double size of void **data_ or allocate space for a single value if empty
 * abort() called on failure
 * ------------------------------
 * @param q: pointer to queue
 */

void
Queue_resize_(struct Queue *q)
{
	if (q->capacity_ == 0) {
		q->capacity_ = 1;
		q->data_     = malloc(sizeof(void *));
	} else {
		q->capacity_ *= 2;

		void **tmp = q->data_;
		q->data_   = malloc(sizeof(void *) * q->capacity_);

		if (q->head_ > q->tail_) {
			memcpy(q->data_, tmp + q->head_, q->data_size_ * q->size_);
		}

		free(tmp);
	}
}