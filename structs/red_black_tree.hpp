#include <memory>

template < class T >
class red_black_tree
{
	enum class color { black, red };

       private:
	T data;
	color c;

	std::unique_ptr< red_black_tree > parent;
	std::unique_ptr< red_black_tree > left_child;
	std::unique_ptr< red_black_tree > right_childe;

	auto
	left_rotate() -> void
	{

	}
};
