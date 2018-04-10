// radixSort implementation

#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

// counting sort working on a single digit
void countSort(std::vector<int> &v, std::function<int(int)> getKey)
{
	int const counter_size    = 19;
	int counter[counter_size] = {0};

	auto v_copy = v;
	// count digits
	for (size_t i = 0; i < v.size(); i++)
		counter[getKey(v_copy[i])]++;
	// add digits that come before
	for (size_t i = 1; i < 19; i++)
		counter[i] += counter[i - 1];

	size_t overflow = -1;
	for (size_t i = v.size() - 1; i != overflow; i--) {
		v[counter[getKey(v_copy[i])] - 1] = v_copy[i];
		counter[getKey(v_copy[i])]--;
	}
}

// sort a digit at a time
int getKey(int a, int b)
{
	if (b > 0) {
		a /= (b * 10);
	}
	a %= 10;
	return a + 9; // -9 -> 0 for easy sorting
}
// sort digit at a time
void radix(std::vector<int> &v, int digits, bool neg)
{
	for (int i = 0; i < digits; i++)
		countSort(v, std::bind(getKey, std::placeholders::_1, i));
}
// count sig figs
void radix(std::vector<int> &v)
{
	int min = *std::min_element(v.begin(), v.end());
	int max = std::max(*std::max_element(v.begin(), v.end()), abs(min));

	bool neg = min < 0;

	int digits = 0;
	while (max) {
		max /= 10;
		digits++;
	}

	radix(v, digits, neg);
}
