#ifndef UTILS_COORDINATES_COORDINATES2D_HPP
#define UTILS_COORDINATES_COORDINATES2D_HPP

#include <array>
#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace utils {

// Not sure how to specify requirement here
template<class T, class U>
concept SameHelper = std::is_same_v<T, U>;

template<class T, class U>
concept SameAs = SameHelper<T, U>;

template<typename T, typename... U>
concept IsSameAsAnyOf = (SameAs<T, U> || ...);

template<class SizeType>
concept TrivialSizeType = requires
{
    IsSameAsAnyOf<SizeType, int, unsigned int, long, unsigned long, long long, unsigned long long>;
};

template<TrivialSizeType SizeType> struct Index2D
{
	constexpr Index2D() = default;
	constexpr Index2D(const Index2D& other) = default;
	constexpr Index2D(Index2D&& other) noexcept = default;
	constexpr Index2D(SizeType initRow, SizeType initCol) : row{initRow}, column{initCol} {};

	~Index2D() = default;

	constexpr auto operator=(const Index2D& other) -> Index2D& = default;
	constexpr auto operator=(Index2D&& other) noexcept -> Index2D& = default;

	auto
	operator==(const Index2D<SizeType>& other) const -> bool
	{
	    return other.row == row && other.column == column;
	}

	SizeType row, column;
};

template<TrivialSizeType SizeType> struct Index2DHash
{
	auto
	operator()(const Index2D<SizeType>& index) const -> long long
	{
	    constexpr auto primeFactor = 53;
	    const auto rowHash = std::hash<SizeType>()(index.row);
	    const auto colHash = std::hash<SizeType>()(index.column);
	    // TODO: Come up with a better hash function
	    return (primeFactor + rowHash) * primeFactor + colHash;
	}
};

template<TrivialSizeType SizeType> struct Coordinate2D
{
	constexpr Coordinate2D() = default;
	constexpr Coordinate2D(const Coordinate2D& other) = default;
	constexpr Coordinate2D(Coordinate2D&& other) noexcept = default;
	constexpr Coordinate2D(SizeType initX, SizeType initY) : x{initX}, y{initY} {};

	~Coordinate2D() = default;

	constexpr auto operator=(const Coordinate2D& other) -> Coordinate2D& = default;
	constexpr auto operator=(Coordinate2D&& other) noexcept -> Coordinate2D& = default;

	auto
	operator==(const Coordinate2D<SizeType>& other) const -> bool
	{
	    return (other.x == x && other.x == x);
	}

	SizeType x, y;
};

template<TrivialSizeType SizeType> struct Coordinate2DHash
{
	auto
	operator()(const Coordinate2D<SizeType>& index) const -> long long
	{
	    constexpr auto primeFactor = 53;
	    const auto rowHash = std::hash<SizeType>()(index.x);
	    const auto colHash = std::hash<SizeType>()(index.y);
	    // TODO: Come up with a better hash function
	    return (primeFactor + rowHash) * primeFactor + colHash;
	}
};

} // namespace utils
#endif