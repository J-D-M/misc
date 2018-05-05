/*
 * Simple queue implementation
 */
#include <algorithm>
#include <stdexcept>

template <typename T> class Queue
{
	T *data;
	size_t capacity_{0};
	size_t size_{0};
	size_t head{0};
	size_t tail{0};

	auto
	resize() -> void
	{
		if (capacity_ == 0) {
			capacity_ = 1;
			data      = new T;
		} else {
			capacity_ *= 2;

			auto tmp = std::move(data);
			data     = new T[capacity_];

			if (head > tail) {
				std::copy(tmp + head, tmp + size_, data);
				std::copy(tmp, tmp + tail, data);
				tail = size_;
			} else {
				std::copy(tmp, tmp + size_, data);
			}

			delete tmp;
		}
	}

      public:
	Queue() {}
	Queue(size_t cap) : capacity_{cap} { data = new T[cap]; }

	~Queue() { delete data; }

	auto
	push_back(T const &x) -> void
	{
		if (size_ == capacity_)
			resize();

		data[tail] = x;
		tail       = (tail + 1) % (capacity_ + 1);
		++size_;
	}

	auto
	pop_front() -> T
	{
		if (!empty()) {
			T tmp = data[head];
			head  = (head + 1) % capacity_;
			--size_;

			return tmp;
		} else {
			throw std::underflow_error(
			    "Attempting to pop empty stack");
		}
	}

	auto
	empty() const -> bool
	{
		return head == tail;
	}

	auto
	size() const -> size_t
	{
		return size_;
	}

	auto
	capacity() const -> size_t
	{
		return capacity_;
	}
};
