/* Quick sort */

#include <cstddef>
#include <ctime>
#include <iterator>

/*
 * partition elements smaller than the pivot to the left
 * move pivot to the left of larger elements
 * return new pivot
 */

template < class Iterator >
auto
partition(Iterator left, Iterator pivot) -> Iterator
{
	for (auto i = left; i < pivot; ++i) {
		if (*i <= *pivot) {
			if (i != left)
				std::iter_swap(i, left);
			++left;
		}
	}

	if (left != pivot)
		std::iter_swap(left, pivot);

	return left;
}

/* recursively sort elements using pivot points */
template < class Iterator >
auto
quick_sort_helper(Iterator begin, Iterator end) -> void
{
	if (begin >= end) {
		return;
	}

	auto pivot = partition(begin, end);

	if (pivot > begin) {
		quick_sort_helper(begin, pivot - 1);
	}

	quick_sort_helper(pivot + 1, end);
}

template < class Iterator >
auto
quick_sort(Iterator begin, Iterator end) -> void
{
	quick_sort_helper(begin, end - 1);
}
