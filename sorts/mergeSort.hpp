#include <algorithm> // copy
#include <cstddef>   // size_t

// merge ordered sub containers
template <class Container>
void merge(Container &v, size_t left, size_t mid, size_t right)
{
	size_t lSize = mid - left + 1;
	size_t rSize = right - mid;

	Container lSub(lSize);
	Container rSub(rSize);

	std::copy(&v[left], &v[mid + 1], &lSub[0]);
	std::copy(&v[mid + 1], &v[right + 1], &rSub[0]);

	size_t i = 0;
	size_t j = 0;

	for (size_t k = left; k <= right; k++) {
		//bounds check then place the smallest value in front
		if (j >= rSize || (i < lSize && lSub[i] <= rSub[j])) {
			v[k] = lSub[i];
			++i;
		} else {
			v[k] = rSub[j];
			++j;
		}
	}
}

// split into smaller sub containers
template <class Container>
void mergeSort(Container &v, size_t left, size_t right)
{
	if (left < right) {
		size_t mid = (left + right) / 2;

		mergeSort(v, left, mid);
		mergeSort(v, mid + 1, right);

		merge(v, left, mid, right);
	}
}

template <class Container>
void mergeSort(Container &v)
{
	if (!v.empty())
		mergeSort(v, 0, v.size() - 1);
}
