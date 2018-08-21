/*
 * Simple queue implementation
 */
#include <algorithm>
#include <stdexcept>

template < typename T >
class queue
{
       public:
	queue()
	{
	}

	~queue()
	{
		delete[] data;
	}

	auto
	push(T const &x) -> void
	{
		if (size_ >= capacity_)
			resize();

		data[tail] = x;
		tail       = (tail + 1) % (capacity_ + 1);
		++size_;
	}

	auto
	pop() -> T
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

       private:
	T *data;
	size_t capacity_{ 0 };
	size_t size_{ 0 };
	size_t head{ 0 };
	size_t tail{ 0 };

	auto
	resize() -> void
	{
		if (capacity_ == 0) {
			capacity_ = 2;
			data      = new T[capacity_];
			return;
		}

		capacity_ *= 2;

		auto tmp = data;
		data     = new T[capacity_];

		if (head > tail) {
			std::copy(tmp + head, tmp + size_, data);
			std::copy(tmp, tmp + tail, data);
			tail = size_;
		} else {
			std::copy(tmp, tmp + size_, data);
		}

		delete[] tmp;
	}
};
