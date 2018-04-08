// Quick sort implementation

#include <algorithm> // swap
#include <cstddef>   // size_t

template <class Container>
size_t partition(Container &c, size_t left, size_t right)
{
	auto pivotElement = c[right];
	// move elements smaller than pivot to left
	for (size_t j = left; j < right; j++) {
		if (c[j] <= pivotElement) {
			if (j != left)
				std::swap(c[left], c[j]);
			left++;
		}
	}
	// move pivot to the left of larger elements
	if (left != right)
		std::swap(c[left], c[right]);
	// return new pivot index
	return left;
}

template <class Container>
void quickSort(Container &c, size_t left, size_t right)
{
	if (left < right) {
		size_t pivotPoint = partition(c, left, right);

		if (pivotPoint != 0) // overflow check
			quickSort(c, left, pivotPoint - 1);
		quickSort(c, pivotPoint + 1, right);
	}
}

template <class Container> void quickSort(Container &c)
{
	quickSort(c, 0, c.size() - 1);
}