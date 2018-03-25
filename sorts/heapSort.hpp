#include <cstddef>   // size_t
#include <algorithm> // swap
#include <limits>    // <size_t>::max()

// heap sort implementation

// make parent and nodes follow max-heap property
template <class Container>
void maxHeapify(Container &v, const size_t size, const size_t parent)
{
        size_t largest     = parent;
        const size_t lNode = 2 * parent;
        const size_t rNode = 2 * parent + 1;

        auto compare =[&size, &largest, &v](size_t a)
        {
                if (a < size && v[a] > v[largest])
                        largest = a;
        };

        compare(lNode);
        compare(rNode);

        if (largest != parent) {
                std::swap(v[parent], v[largest]);
                maxHeapify(v, size, largest);
        }
}

// max-heapify container
template <class Container>
void buildMaxHeap(Container &v)
{
        const size_t overflow = std::numeric_limits<size_t>::max();
        size_t i              = (v.size() - 1) / 2;

        for (; i != overflow; i--)
                maxHeapify(v, v.size(), i);
}

template <class Container>
void heapSort(Container &v)
{
        buildMaxHeap(v);
        size_t size = v.size();

        // push largest to the end
        // max-heapify remainder of elements
        for (auto i = v.size() - 1; i > 0; i--) {
                std::swap(v[0], v[i]);
                --size;
                maxHeapify(v, size, 0);
        }
}
