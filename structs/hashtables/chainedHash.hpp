#include <list>
#include <string>
#include <vector>

template <typename Key, typename Elem> class ChainedHash
{
      private:
	std::vector<std::list<Elem>> data;
	size_t size;

	auto hash(Key const &k) -> size_t;

      public:
	ChainedHash() {}
	~ChainedHash() {}

	auto insert(Key const &k, Elem const &e) const -> void
	{
		if (size > data.size * 0.7)
			data.resize(data.size * 2);

		data[find(k)] = e;
	}

	auto find(Key &) const -> Elem &;
	auto del(Key &) const -> void;

	auto operator[](Key const &k) const -> Elem & { return find(k); }

};

template <typename Elem>
auto ChainedHash<std::string, Elem>::hash(std::string const &str) -> size_t {
	return 1;
}


