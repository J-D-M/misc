#include <limits>
#include <vector>

template < class Container >
auto
countSort(Container &nums, int const max) -> void
{
	const auto nums_size{ std::size(nums) };
	const auto counter_size{ max + 1 };
	const auto overflow{ std::numeric_limits< size_t >::max() };

	auto copy{ std::vector< int >(nums_size) };
	auto counter{ std::vector< int >(max + 1) };

	// count the amount of elements equal to i
	for (auto i = 0; i < nums_size; i++)
		++counter[nums[i]];

	// add the amount of elements less than i
	for (auto i = 1; i < counter_size; i++)
		counter[i] += counter[i - 1];

	for (auto i = nums_size - 1; i != overflow; i--) {
		// element count starts at 1 not 0
		copy[counter[nums[i]] - 1] = nums[i];
		counter[nums[i]]--;
	}

	std::copy(std::begin(nums), std::end(nums), std::begin(copy));
}
