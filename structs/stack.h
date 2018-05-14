#ifndef _JDM_STACK_
#define _JDM_STACK_

#include <stdbool.h>
#include <stddef.h>

struct Stack;
size_t stackSize(struct Stack *);
void stackPush(struct Stack *);
void *stackPop(struct Stack *);
void stackPush(struct Stack *, void *);
bool stackEmpty(struct Stack *);

#endif