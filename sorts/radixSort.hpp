// radixSort implementation

#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

// counting sort working on a single digit
void countSort(std::vector<int> &v, std::function<int(int)> getKey)
{
	auto v_copy     = v;
	int counter[10] = {0};

	for (size_t i = 0; i < v.size(); i++)
		counter[getKey(v_copy[i])]++;

	for (size_t i = 1; i < 10; i++)
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
	return b > 0 ? abs(a / (b * 10)) % 10 : abs(a % 10);
}

void radix(std::vector<int> &v, int digits, bool neg)
{
	for (int i = 0; i < digits; i++)
		countSort(v, std::bind(getKey, std::placeholders::_1, i));

	if (neg)
		countSort(v, [](int a) { return a < 0 ? 0 : 1; });
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
