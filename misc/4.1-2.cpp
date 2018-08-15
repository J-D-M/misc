#include <tuple>
#include <vector>

template <class T>

std::tuple<size_t, size_t, T> maxSubB(
                std::vector<T> &v,
                size_t const &lower,
                size_t const &upper
                )
{
        if (v.empty()) { return std::make_tuple(0, 0, 0); }

        T sum           = v[0];
        T maxSum        = v[0];
        size_t maxLower = 0;
        size_t maxUpper = 0;

        for (size_t i = lower; i <= upper; i++) {
                sum = v[i];

                if (sum > maxSum) {
                        maxSum   = sum;
                        maxLower = maxUpper = i;
                }

                for (size_t j = i + 1; j <= upper; j++) {
                        sum += v[j];
                        if (sum > maxSum) {
                                maxSum   = sum;
                                maxLower = i;
                                maxUpper = j;
                        }
                }
        }

        return std::make_tuple(maxLower, maxUpper, maxSum);
}

template <class T>

std::tuple<size_t, size_t, T> maxSubB (std::vector<T> &v)
{
        return maxSubB(v, 0, v.size() - 1);
}
