/* Merge sort */

#include <algorithm>
#include <cstddef>
#include <vector>

/* merge sorted subcontainers */
template < class Iterator >
auto
merge(Iterator left, Iterator mid, Iterator right) -> void
{
	auto left_container = std::vector< typename Iterator::value_type >(
	    std::distance(left, mid) + 1);

	auto right_container = std::vector< typename Iterator::value_type >(
	    std::distance(mid, right));

	std::copy(left, mid + 1, std::begin(left_container));
	std::copy(mid + 1, right + 1, std::begin(right_container));

	auto lc_iter = std::begin(left_container);
	auto rc_iter = std::begin(right_container);

	const auto l_end = std::end(left_container);
	const auto r_end = std::end(right_container);

	for (auto i = left; i <= right; ++i) {
		/* bounds checking */
		if (rc_iter != r_end
		    && (lc_iter == l_end || *rc_iter < *lc_iter)) {
			*i = *rc_iter;
			++rc_iter;
		} else {
			*i = *lc_iter;
			++lc_iter;
		}
	}
}

/* recursivly split into smaller containers */
template < typename Iterator >
auto
merge_sort_helper(Iterator begin, Iterator end) -> void
{
	if (begin >= end) {
		return;
	}

	auto mid_iter = begin;
	advance(mid_iter, std::distance(begin, end) / 2);

	merge_sort_helper(begin, mid_iter);
	merge_sort_helper(mid_iter + 1, end);

	merge(begin, mid_iter, end);
}

template < typename Iterator >
auto
merge_sort(Iterator begin, Iterator end) -> void
{
	merge_sort_helper(begin, end - 1);
}
