#include <memory>
#include <optional>

template < class T >
class binary_tree
{
       public:
	binary_tree(const T x);

	binary_tree();

	auto insert(const T x) -> void;
	auto erase(const T x) -> void;
	auto empty() -> bool;

	friend auto
	operator<<(std::ostream &os, const binary_tree< T > &b_t)
	    -> std::ostream &
	{
		if (!b_t.data) {
			return os;
		}

		if (b_t.left_child) {
			os << *b_t.left_child << ", ";
		}

		os << *b_t.data;

		if (b_t.right_child) {
			os << ", " << *b_t.right_child;
		}

		return os;
	}

       private:
	std::unique_ptr< T > data;
	std::unique_ptr< binary_tree > left_child;
	std::unique_ptr< binary_tree > right_child;

	auto yank() -> void;
};

/* constructors */
template < class T >
binary_tree< T >::binary_tree(const T x)
    : data{ std::make_unique< T >(x) }
    , left_child{ nullptr }
    , right_child{ nullptr }
{
}

template < class T >
binary_tree< T >::binary_tree()
    : data{ nullptr }, left_child{ nullptr }, right_child{ nullptr }
{
}

/* insert element */
template < class T >
auto
binary_tree< T >::insert(const T x) -> void
{
	if (!data) {
		data = std::make_unique< T >(x);
		return;
	}

	const auto l_inser = [&](auto &child) {
		if (!child) {
			child = std::make_unique< binary_tree >(x);
		} else {
			child->insert(x);
		}
	};

	if (x > *data) {
		l_inser(right_child);
	} else if (x != *data) {
		l_inser(left_child);
	}
}

/* swap elements to avoid empty parents */

template < class T >
auto
binary_tree< T >::yank() -> void
{
	if (data) {
		return;
	}

	const auto l_yank = [&](auto &child) {
		data = std::move(child->data);
		child->yank();

		if (child->empty()) {
			child = nullptr;
		}
	};

	if (right_child)
		l_yank(right_child);
	else if (left_child)
		l_yank(left_child);
}

/* erase element */
template < class T >
auto
binary_tree< T >::erase(const T x) -> void
{
	if (!data) {
		return;
	}

	if (x == *data) {
		data = nullptr;
		yank();
	} else if (x > *data) {
		right_child->erase(x);
	} else {
		left_child->erase(x);
	}
}

/* check if node is empty */
template < class T >
auto
binary_tree< T >::empty() -> bool
{
	return data == nullptr;
}
