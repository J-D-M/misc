// priority queue implementation
#include <initializer_list>
#include <stdexcept>
#include <vector>

template <typename T> class pQueue
{
      private:
	std::vector<T> heap;

	size_t getP(size_t const &c) { return (c - 1) / 2; } // parent
	size_t getL(size_t const &p) { return p * 2 + 1; }   // Left child
	size_t getR(size_t const &p) { return p * 2 + 2; }   // Right child

	// Increase value of element and reorder queue
	void increaseKey(size_t i, T const &val)
	{
		if (val < heap[i]) // new val must be larger
			throw std::runtime_error(
			    "Error: new key smaller that current value");

		heap[i] = val;

		for (size_t parent = getP(i); i > 0 && heap[i] > heap[parent];
		     parent	= getP(parent)) {
			std::swap(heap[i], heap[parent]);
			i = parent;
		}
	}

	// make heap follow max heap property
	void maxHeapify(const size_t parent)
	{
		size_t largest     = parent;
		const size_t len   = heap.size();
		const size_t lNode = getL(parent);
		const size_t rNode = getR(parent);

		if (lNode < len && heap[lNode] > heap[largest])
			largest = lNode;
		if (rNode < len && heap[rNode] > heap[largest])
			largest = rNode;

		if (largest != parent) {
			std::swap(heap[parent], heap[largest]);
			maxHeapify(largest);
		}
	}

      public:
	T max() { return heap[0]; }; // first element is largest in max heap
	bool empty(void) { return heap.empty(); }; // check if heap is empty

	// push element onto queue
	void push(const T &val)
	{
		heap.push_back(val);
		increaseKey(heap.size() - 1, val);
	}
	// pop and return element in front
	T pop()
	{
		if (empty()) {
			throw std::runtime_error("Error: Queue empty");
		}

		T max   = heap[0];
		heap[0] = heap.back();

		heap.pop_back();
		maxHeapify(0);

		return max;
	}

	// constructors
	pQueue() : heap(){};

	pQueue(std::initializer_list<T> ls)
	{
		for (auto &l : ls)
			push(l);
	}

	template <class Container> pQueue(Container &ls)
	{
		for (auto &l : ls)
			push(l);
	}

	template <class Container> pQueue(Container &&ls)
	{
		for (auto &l : ls)
			push(l);
	}
};
