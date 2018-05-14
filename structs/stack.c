#include "./stack.h"
#include <stdbool.h> // bools
#include <stdlib.h>  // free, realloc, size_t
#include <string.h>  // memcpy


struct Stack {
	size_t data_size_;
	size_t size_;
	size_t capacity_;
	void **data_;
};

bool
Stack_resize_(struct Stack *s)
{
	if (s->capacity_ == 0)
		s->capacity_ = 1;
	else
		s->capacity_ *= 2;

	void *tmp = realloc(s, sizeof(void *) * s->capacity_);

        if (tmp == NULL)
                return false;
        
        s = tmp;
        return true;
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

void
stackFree(struct Stack *s)
{
	for (size_t i = 0; i < s->size_; i++) {
		free(s->data_[i]);
	}

	free(s->data_);
	free(s);
}

bool
stackPush(struct Stack *s, void *x)
{
	if (s->size_ == s->capacity_)
		if (!Stack_resize_(s))
			return false;

        memcpy(x, s->data_[s->size_], s->data_size_);
        s->size_++;

        return s->data_[s->size_ - 1] != NULL;
}

void *
stackPop(struct Stack*s)
{
        if (s->size_ == 0)
                return NULL;
        void *ret = s->data_[s->size_];
        s->size_--;
        return ret;
}