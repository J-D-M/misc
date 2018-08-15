#ifndef LINKED_LIST
#define LINKED_LIST
#include <stddef.h>

struct List {
	size_t data_size_;
	void *data_;
	struct List *prev_;
	struct List *next_;
};

#endif
