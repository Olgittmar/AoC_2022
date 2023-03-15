#include "Rope.hpp"

#include "Definitions.hpp"

#include <cmath>
#include <string>

namespace Solutions::RopeBridge {

template<utils::TrivialSizeType LengthType, utils::TrivialSizeType DistType, size_t RopeLength>
auto
Rope<LengthType, DistType, RopeLength>::moveHead(Direction dir) -> Position_t
{
    // Move m_headPos
    auto& headPos = m_knots.front();

    using enum Direction;
    switch (dir)
	{
	    case Up:
		++headPos.y;
		break;
	    case Down:
		--headPos.y;
		break;
	    case Left:
		--headPos.x;
		break;
	    case Right:
		++headPos.x;
		break;
	}

    updateKnotPositions(dir);
    return getTailPos();
}

template<utils::TrivialSizeType LengthType, utils::TrivialSizeType DistType, size_t RopeLength>
auto
Rope<LengthType, DistType, RopeLength>::makeMotion(std::string_view line) -> Motion
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

template<utils::TrivialSizeType LengthType, utils::TrivialSizeType DistType, size_t RopeLength>
void
Rope<LengthType, DistType, RopeLength>::follow(Position_t leader, Position_t& follower, Direction dir)
{
    using enum Direction;

    switch (dir)
	{
	    case Up:
		{
		    if (leader.y > follower.y)
			{
			    follower.x = leader.x;
			    if (leader.y > follower.y + 1)
				{
				    ++(follower.y);
			    }
		    }
		    break;
		}
	    case Down:
		{
		    if (leader.y < follower.y)
			{
			    follower.x = leader.x;
			    if (leader.y + 1 < follower.y)
				{
				    --(follower.y);
			    }
		    }
		    break;
		}
	    case Left:
		{
		    if (leader.x < follower.x)
			{
			    follower.y = leader.y;
			    if (leader.x + 1 < follower.x)
				{
				    --(follower.x);
			    }
		    }
		    break;
		}
	    case Right:
		{
		    if (leader.x > follower.x)
			{
			    follower.y = leader.y;
			    if (leader.x > follower.x + 1)
				{
				    ++(follower.x);
			    }
		    }
		    break;
		}
	}
}

template<utils::TrivialSizeType LengthType, utils::TrivialSizeType DistType, size_t RopeLength>
void
Rope<LengthType, DistType, RopeLength>::updateKnotPositions(Direction dir)
{
    auto exceedsPlanckLength = [](Position_t lhs, Position_t rhs) -> bool
    {
	const auto hDiff = std::abs(lhs.x - rhs.x);
	const auto vDiff = std::abs(lhs.y - rhs.y);
	return (hDiff > 1 || vDiff > 1);
    };

    for (size_t idx = 1; idx < m_knots.size(); ++idx)
	{
	    const auto predecessor = m_knots.at(idx - 1);
	    auto& knot = m_knots.at(idx);

	    if (!exceedsPlanckLength(predecessor, knot))
		{
		    continue;
	    }

	    follow(predecessor, knot, dir);
	}
}

template class Rope<LengthType_t, DistType_t, ShortRopeLength>;
template class Rope<LengthType_t, DistType_t, LongRopeLength>;
} // namespace Solutions::RopeBridge