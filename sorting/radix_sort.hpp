/* radixSort implementation */

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
#include <vector>

/* counting sort working on a single digit */
template < class Container, class Func >
auto
count_sort(Container &nums, Func &&get_key) -> void
{
	auto nums_copy          = nums;
	const auto nums_size    = std::size(nums);
	const auto counter_size = size_t{ 19 };

	int counter[counter_size] = { 0 };

	for (auto i = 0; i < std::size(nums); i++) {
		counter[get_key(nums[i])]++;
	}

	for (auto i = 1; i < 19; i++) {
		counter[i] += counter[i - 1];
	}

	auto overflow = std::numeric_limits< size_t >::max();

	for (auto i = size_t{ nums_size - 1 }; i != overflow; i--) {
		nums[counter[get_key(nums_copy[i])] - 1] = nums_copy[i];
		counter[get_key(nums_copy[i])]--;
	}
}

/* sort a digit at a time */
auto
get_key(int a, int b) -> int
{
	if (b > 0) {
		a /= (b * 10);
	}
	a %= 10;

	return a + 9; /* -9 -> 0 for easy sorting */
}

/* sort digit at a time */
template < class Container >
auto
radix_helper(Container &nums, int digits, bool neg) -> void
{
	for (auto i = 0; i < digits; i++) {
		count_sort(nums, [&](int a) { return get_key(a, i); });
	}
}

/* count sig figs */
template < class Container >
auto
radix_sort(Container &num) -> void
{
	auto min = *std::min_element(std::begin(num), std::end(num));
	auto max = std::max(*std::max_element(std::begin(num), std::end(num)),
	                    abs(min));

	auto neg    = min < 0;
	auto digits = int{ 0 };

	while (max) {
		max /= 10;
		digits++;
	}

	radix_helper(num, digits, neg);
}
