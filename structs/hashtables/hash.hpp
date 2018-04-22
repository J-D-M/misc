#include <utility>

template <typename Key, typename Elem> class Hash
{

	size_t hash(Key &);

      public:
	void insert(Key const &, Elem const &);
	void find(Key &);
	void del(Key &);
};
