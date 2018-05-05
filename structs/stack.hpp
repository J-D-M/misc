/*
 * Simple stack implementation
 */
#include <algorithm>
#include <stdexcept>

template <typename T> class Stack
{
	T *data;
	size_t size{0};
	size_t capacity{0};

	auto
	resize() -> void
	{
		if (capacity == 0) {
			++capacity;
			data = new T;
		} else {
			capacity *= 2;

			auto tmp = std::move(data);
			data     = new T[capacity];
			std::copy(tmp, tmp + (size - 1), data);

			delete tmp;
		}
	}

      public:
	Stack() {}
	Stack(size_t capacity_) : capacity{capacity_}
	{
		data = new T[capacity_];
	};

	~Stack() { delete data; }

	auto
	empty() const -> bool
	{
		return size == 0;
	}

	auto
	push(T const &x) -> void
	{
		if (size == capacity)
			resize();
		data[size] = x;
		size++;
	}

	auto
	pop() -> T
	{
		if (!empty()) {
			return data[(size-- - 1)];
		} else {
			throw std::underflow_error(
			    "Attempting to pop empty stack");
		}
	}

	auto
	getSize() const -> size_t
	{
		return size;
	}

	auto
	getCapacity() const -> size_t
	{
		return capacity;
	}
};
