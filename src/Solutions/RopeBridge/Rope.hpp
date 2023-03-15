#ifndef SOLUTIONS_ROPEBRIDGE_ROPE_HPP
#define SOLUTIONS_ROPEBRIDGE_ROPE_HPP

#include "Utils.hpp"

#include <cstddef>

namespace Solutions::RopeBridge {

template<utils::TrivialSizeType LengthType, utils::TrivialSizeType DistType, size_t RopeLength> class Rope
{
    public:

	using Position_t = utils::Coordinate2D<LengthType>;

	enum class Direction
	{
	    Up,
	    Down,
	    Left,
	    Right,
	};

	struct Motion
	{
		Direction direction;
		LengthType distance;
	};

	// If only 2 position values are given, assume that Head should overlap Tail
	constexpr Rope() = default;
	constexpr Rope(LengthType row, LengthType col) : m_knots{Position_t{row, col}} {}

	auto
	getHeadPos() const -> Position_t
	{
	    return m_knots.front();
	}

	auto
	getTailPos() const -> Position_t
	{
	    return m_knots.back();
	}

	// Move head one step in the specified direction,
	// returns the (potentially) new position of the tail
	auto moveHead(Direction dir) -> Position_t;
	static auto makeMotion(std::string_view line) -> Motion;

    private:

	static inline constexpr auto
	charToDir(char dirChar) -> Direction
	{
	    using enum Direction;
	    switch (dirChar)
		{
		    case 'U':
			return Up;
		    case 'D':
			return Down;
		    case 'L':
			return Left;
		    case 'R':
			return Right;
		    default:
			{
			    throw std::invalid_argument(std::string("No known conversion rule from ") + dirChar +
							" to Rope::Direction.");
			}
		}
	}

	void updateKnotPositions(Direction dir);
	void follow(Position_t leader, Position_t& follower, Direction dir);

	std::array<Position_t, RopeLength> m_knots;
};

} // namespace Solutions::RopeBridge
#endif