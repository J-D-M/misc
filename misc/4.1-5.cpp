#include <tuple>
#include <vector>
#include <limits>

template <class T>

std::tuple<size_t, size_t, T> maxSubL(
                std::vector<T> &v,
                size_t const &lower,
                size_t const &upper
                )
{
        if (v.empty()) { return std::make_tuple(0, 0, 0); }

        T sum           = std::numeric_limits<T>::min();
        T maxSum        = v[0];
        size_t maxLower = 0;
        size_t maxUpper = 0;

        for (size_t i = lower; i <= upper; i++) {
                if (sum > maxSum) {
                        maxSum   = sum;
                        maxUpper = i;
                }

                sum += v[i];
        }

        sum = std::numeric_limits<T>::min();

        for (size_t i = maxUpper; i >= lower && i != -1; i--) {
                sum += v[i];

                if (sum > maxSum) {
                        maxSum   = sum;
                        maxLower = i;
                }
        }

        return std::make_tuple(maxLower, maxUpper, maxSum);
}

template <class T>

std::tuple<size_t, size_t, T> maxSubL (std::vector<T> &v)
{
        return maxSubB(v, 0, v.size() - 1);
}
