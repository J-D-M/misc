#include "./stack.h"
#include <stdbool.h> // bools
#include <stdio.h>   // perror
#include <stdlib.h>  // free, realloc, size_t
#include <string.h>  // memcpy

/*
 * Stack implementation
 */

struct Stack {
	size_t data_size_; // Size in bytes of data to hold (int, char, etc..)
	size_t size_;      // Number of values currently held
	size_t capacity_;  // Total capacity of current stack
	void **data_;      // data container
};

/*
 * Function: stackNew
 * allocated and initialize memory for new stack
 * ------------------------------
 *  @param data_size: size of data to be held, the type of stack
 *  returns: new initialized stack
 */

struct Stack *
stackNew(size_t data_size)
{
	struct Stack *ret_stack = malloc(sizeof(struct Stack));

	ret_stack->data_size_ = data_size;
	ret_stack->capacity_  = 0;
	ret_stack->size_      = 0;
	ret_stack->data_      = NULL;

	return ret_stack;
}

/*
 * Function: Stack_resize_
 * double size of void **data_ or allocate space for a single value if empty
 * abort() called on failure
 * ------------------------------
 * @param s: pointer to stack
 */

void
Stack_resize_(struct Stack *s)
{
	if (s->capacity_ == 0)
		s->capacity_ = 1;
	else
		s->capacity_ *= 2;

	void **tmp = realloc(s->data_, sizeof(void *) * s->capacity_);

	if (tmp == NULL) {
		perror("ERROR: Failed to resize stack\n");
		abort();
	}

	s->data_ = tmp;

	for (size_t i = s->size_; i < s->capacity_; i++)
		s->data_[i] = NULL;
}

/*
 * Function: stackFree
 * free all memory allocated on stack struct
 * ----------------------------------------
 *  @param s: pointer to stack to be free'ed
 */

void
stackFree(struct Stack *s)
{
	for (size_t i = 0; i < s->capacity_ && s->data_[i] != NULL; i++) {
		free(s->data_[i]);
	}

	free(s->data_);
	free(s);
}

/*
 * Function: stackPush
 * push element onto stack
 * --------------------------
 *  @param s: pointer to stack
 *  @param x: element to add to stack
 */

void
stackPush(struct Stack *s, void *x)
{
	if (s->size_ == s->capacity_)
		Stack_resize_(s);

	if (s->data_[s->size_] == NULL)
		s->data_[s->size_] = malloc(s->data_size_);

	memcpy(s->data_[s->size_], x, s->data_size_);
	s->size_++;
}

/*
 * Function: stackPop
 * pop element off stack
 * print error and abort() on underflow
 * ----------------------
 *  @param s: pointer to stack
 */

void *
stackPop(struct Stack *s)
{
	if (stackEmpty(s)) {
		perror("ERROR: Stack underflow");
		abort();
	}

	void *ret = s->data_[--s->size_];

	return ret;
}

/*
 * Function: stackPeek
 * peek stack
 * ---------------------
 *  @param s: stack pointer
 *  returns: NULL if empty pointer to top of stack otherwise
 */

void *
stackPeek(struct Stack *s)
{
	if (stackEmpty(s))
		return NULL;

	return s->data_[s->size_ - 1];
}

size_t
stackSize(struct Stack *s)
{
	return s->size_;
}

size_t
stackCapacity(struct Stack *s)
{
	return s->capacity_;
}

bool
stackEmpty(struct Stack *s)
{
	return s->size_ == 0;
}
