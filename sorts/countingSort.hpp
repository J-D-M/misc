#include <vector>

std::vector<int> countSort(std::vector<int> const &vec, int const max)
{
	std::vector<int> ret(vec.size());
	std::vector<int> counter(max + 1);

	// count the amount of elements equal to i
	for (size_t i = 0; i < vec.size(); i++)
		++counter[vec[i]];
	// add the amount of elements less than i
	for (size_t i = 1; i < counter.size(); i++)
		counter[i] += counter[i - 1];

	for (size_t i = 0; i < vec.size(); i++) {
		// element count starts at 1 not 0
		ret[counter[vec[i]] - 1] = vec[i];
		counter[vec[i]]--;
	}

	return ret;
}
