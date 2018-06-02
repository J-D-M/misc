#include <stdlib.h>
#include <string.h>
//#include <string.h>

#include "linkedList.h"

/*
 * Linked list implementation
 */

struct List *
listNew(size_t data_size)
{
	struct List *ret = malloc(sizeof(struct List));

	ret->data_size_ = data_size;
	ret->data_      = NULL;
	ret->prev_      = ret;
	ret->next_      = NULL;

	return ret;
}

void
list_free_node_(struct List *ls)
{
	free(ls->data_);
	free(ls);
}

void
listFree(struct List *ls)
{
	if (ls != ls->prev_)
		listFree(ls->next_);

	list_free_node_(ls);
}

void
listInsert(struct List *head, void *d)
{
	struct List *newLs = listNew(head->data_size_);
	memcpy(newLs, d, newLs->data_size_);

	newLs->prev_        = head;
	newLs->next_        = head->next_;
	newLs->next_->prev_ = newLs;
	head->next_         = newLs;
}

struct List *
listFind(struct List *ls, void *x, int *compare(void *, void *))
{
	struct List *l = ls->next_;

	while (l != l->prev_ && !(*compare(l->data_, x)))
		l = l->next_;

	return l;
}

void
listDelete(struct List *ls, void *x, int *compare(void *, void *))
{
	struct List *l = listFind(ls, x, compare);

	if (l) {
		if (l->next_)
			l->next_->prev_ = l->prev_;
		l->prev_->next_ = l->next_;

		list_free_node_(l);
	}
}
