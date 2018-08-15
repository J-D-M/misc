#include <tuple>
#include <vector>
#include <algorithm>

/*
 * Takes a vector and returns the indices and sum of the largest subarray
 */

//find largest overlapping subarray in range

auto emptyTup = std::make_tuple(0, 0, 0);
template<typename T>

std::tuple<size_t, size_t, T> maxOverlapping(
                std::vector<T> const &vec,
                size_t low,
                size_t mid,
                size_t high
                )
{


        size_t maxLeft  = mid;
        size_t maxRight = mid + 1;
        T sum           = 0;
        T leftSum       = vec[mid];
        T rightSum      = (mid < high) ? vec[mid+1] : mid;

        for (size_t i = mid; i >= low && i <= mid; i--) {
                sum += vec[i];

                if (sum > leftSum) {
                        leftSum = sum;
                        maxLeft = i;
                }
        }

        sum = 0;

        for (size_t i = mid + 1; i <= high; i++) {
                sum += vec[i];

                if (sum > rightSum) {
                        rightSum = sum;
                        maxRight = i;
                }
        }

        return std::make_tuple(maxLeft, maxRight, leftSum + rightSum);
}

template<typename T>

std::tuple<size_t, size_t, T> maxSubArray(
                std::vector<T> const & vec,
                size_t low,
                size_t high
                )
{
        if (vec.empty()) {
                return emptyTup;
        } else if (high == low) {
                return std::make_tuple(low, high, vec[low]);
        }

        //split in half and test the overlapping section
        auto mid     = (low + high) / 2;
        auto left    = maxSubArray(vec, low, mid);
        auto right   = maxSubArray(vec, mid + 1, high);
        auto overlap = maxOverlapping(vec, low, mid, high);

        //return largest of the three
        return std::max( {left, right, overlap},
                        [](auto const &a, auto const &b)
                        {
                        return std::get<2>(a) < std::get<2>(b);
                        }
                       );
}

//defaults to entire vector range
template<typename T>

std::tuple<size_t, size_t, T> maxSubArray(std::vector<T> const &vec)
{
        if (vec.empty()) {
                return emptyTup;
        }

        return maxSubArray(vec, 0, vec.size() - 1);
}
