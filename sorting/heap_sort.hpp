/*
 * Heapsort implementation
 */

#include <algorithm>
#include <iterator>

/* make parent and node follow max-heap property */
template < class Iterator >
auto
max_heapify(Iterator begin, const size_t parent, const size_t size) -> void
{
	const auto l_child{ parent * 2 + 1 };
	const auto r_child{ parent * 2 + 2 };

	auto largest{ parent };

	auto compare = [&](const auto child) {
		if ((child < size) && *(begin + child) > *(begin + parent))
			largest = child;
	};

	compare(l_child);
	compare(r_child);

	if (largest != parent) {
		std::iter_swap((begin + parent), (begin + largest));
		max_heapify(begin, largest, size);
	}
}

template < class Iterator >
auto
build_max_heap(Iterator begin, const size_t size) -> void
{
	const auto overflow{ std::numeric_limits< size_t >::max() };

	for (auto i{ (size - 1) / 2 }; i != overflow; i--) {
		max_heapify(begin, i, size);
	}
}

template < class Iterator >
auto
heap_sort(Iterator begin, Iterator end) -> void
{
	auto size{ std::distance(begin, end) };
	build_max_heap(begin, size);

	for (auto i{ end - 1 }; i != begin; --i) {
		std::iter_swap(begin, i);
		--size;
		max_heapify(begin, 0, size);
	}
}
