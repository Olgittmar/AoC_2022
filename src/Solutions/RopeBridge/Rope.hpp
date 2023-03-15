#ifndef SOLUTIONS_ROPEBRIDGE_ROPE_HPP
#define SOLUTIONS_ROPEBRIDGE_ROPE_HPP

#include "Utils.hpp"

#include <cstddef>

namespace Solutions::RopeBridge {

template<utils::TrivialSizeType LengthType, utils::TrivialSizeType DistType> class Rope
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
	constexpr Rope(LengthType row, LengthType col) : m_headPos{row, col}, m_tailPos{row, col} {}
	constexpr Rope(Position_t headPos, Position_t tailPos) : m_headPos{headPos}, m_tailPos{tailPos} {}

	auto
	getHeadPos() const -> Position_t
	{
	    return m_headPos;
	}

	// Move head one step in the specified direction,
	// returns the (potentially) new position of the tail
	auto
	moveHead(Direction dir) -> Position_t
	{
	    // Move m_headPos
	    using enum Direction;
	    switch (dir)
		{
		    case Up:
			++m_headPos.y;
			break;
		    case Down:
			--m_headPos.y;
			break;
		    case Left:
			--m_headPos.x;
			break;
		    case Right:
			++m_headPos.x;
			break;
		}

	    updateTailPos(dir);
	    return m_tailPos;
	}

	static auto
	makeMotion(std::string_view line) -> Motion
	{
	    if (line.empty())
		{
		    throw std::out_of_range("Cannot convert empty line to motion");
	    }
	    constexpr auto delimiter = ' ';
	    const auto delimPos = line.find(delimiter);
	    const auto distanceStr = line.substr(delimPos);

	    const auto dir = charToDir(line.at(0));
	    const auto dist = std::stol(std::string{distanceStr});

	    const Motion _ret{.direction = dir, .distance = dist};
	    return _ret;
	}

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

	void
	updateTailPos(Direction dir)
	{
	    const auto hDiff = std::abs(m_headPos.x - m_tailPos.x);
	    const auto vDiff = std::abs(m_headPos.y - m_tailPos.y);
	    if (!(hDiff > 1 || vDiff > 1))
		{
		    return;
	    }

	    using enum Direction;
	    switch (dir)
		{
		    case Up:
			{
			    if (m_headPos.y > m_tailPos.y)
				{
				    m_tailPos.x = m_headPos.x;
				    if (m_headPos.y > m_tailPos.y + 1)
					{
					    ++(m_tailPos.y);
				    }
			    }
			    break;
			}
		    case Down:
			{
			    if (m_headPos.y < m_tailPos.y)
				{
				    m_tailPos.x = m_headPos.x;
				    if (m_headPos.y + 1 < m_tailPos.y)
					{
					    --(m_tailPos.y);
				    }
			    }
			    break;
			}
		    case Left:
			{
			    if (m_headPos.x < m_tailPos.x)
				{
				    m_tailPos.y = m_headPos.y;
				    if (m_headPos.x + 1 < m_tailPos.x)
					{
					    --(m_tailPos.x);
				    }
			    }
			    break;
			}
		    case Right:
			{
			    if (m_headPos.x > m_tailPos.x)
				{
				    m_tailPos.y = m_headPos.y;
				    if (m_headPos.x > m_tailPos.x + 1)
					{
					    ++(m_tailPos.x);
				    }
			    }
			    break;
			}
		}
	}

	Position_t m_headPos{};
	Position_t m_tailPos{};
};

} // namespace Solutions::RopeBridge
#endif