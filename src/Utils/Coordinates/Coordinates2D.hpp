#ifndef UTILS_COORDINATES_COORDINATES2D_HPP
#define UTILS_COORDINATES_COORDINATES2D_HPP

#include <concepts>
#include <type_traits>
#include <utility>

namespace utils {

// Not sure how to specify requirement here
template<typename SizeType>
concept TrivialSizeType = requires(SizeType&& sizeType)
{
    true;
};

template<TrivialSizeType SizeType> struct Index2D
{
	SizeType row, column;
};

template<TrivialSizeType SizeType> struct Coordinate2D
{
	SizeType x, y;
};

} // namespace utils
#endif