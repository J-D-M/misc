#ifndef _JDM_STACK_
#define _JDM_STACK_

#include <stdbool.h>
#include <stddef.h>

struct Stack;
struct Stack *stackNew(size_t);
void stackFree(struct Stack *);
void stackPush(struct Stack *, void *);
void *stackPop(struct Stack *);
void *stackPeek(struct Stack *);
bool stackEmpty(struct Stack *);
size_t stackSize(struct Stack *);
size_t stackCapacity(struct Stack *);

#endif
