#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <list>
#include <string>
#include <utility>
#include <vector>

template <typename Key, typename Elem> class ChainedHash
{
      private:
	std::vector<std::list<std::pair<Key, Elem>>> data; // table
	size_t elements;
	size_t capacity;
	std::pair<Key, Elem> default_pair;

	// primality check for resize()
	auto isPrime(size_t x) const -> bool
	{
		size_t max = sqrt(x);
		for (size_t i = 2; i < max; i++)
			if (x % i == 0)
				return false;
		return true;
	}

	// get new size of table
	auto resize() const -> void
	{
		// find next prime
		if (capacity == 0) {
			capacity = 7;
		} else {
			capacity *= 2;
			while (!isPrime(capacity))
				capacity++;
		}

		// temp copy
		auto tmp = data;
		data.clear();
		data.resize(capacity);
		// push everything back in with new hash
		for (auto const &ls : data)
			for (auto const &elem : ls)
				insert(elem);
	}

	auto hash(Key const &k) -> size_t;

      public:
	// insert elem
	auto insert(Key const &k, Elem const &e) const -> void
	{
		auto ls    = data[hash(k)];
		auto itter = std::find(ls.begin(), ls.end(), k);

		if (itter != ls.end())
			*itter = e;
		else
			ls.push_back(e);

		elements++;
	}

	// delete element
	auto del(Key const &k) const -> void
	{
		auto ls    = data[hash(k)];
		auto itter = std::find(ls.begin(), ls.end(), k);

		if (itter != ls.end()) {
			ls.erase(itter);
			elements--;
		}
	}

	auto size() const -> size_t { return elements; }

	ChainedHash() {}

	ChainedHash(std::initializer_list<std::pair<Key, Elem>> ls)
	{
		for (auto const &l : ls)
			insert(l.first, l.second);
	}

	~ChainedHash() {}
};
