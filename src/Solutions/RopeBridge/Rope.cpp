#include "Rope.hpp"

#include "Definitions.hpp"
#include "PrettyPrint/PrettyPrint.hpp"

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
Rope<LengthType, DistType, RopeLength>::updateKnotPositions(Direction dir)
{
    for (size_t idx = 1; idx < m_knots.size(); ++idx)
	{
	    const auto leader = m_knots.at(idx - 1);
	    auto& follower = m_knots.at(idx);

	    const auto vDiff = leader.y - follower.y;
	    const auto hDiff = leader.x - follower.x;

	    // TODO: Pretty sure these two can be generalized to something nicer.
	    if (std::abs(vDiff) > 1)
		{
		    follower.y += static_cast<LengthType>(vDiff > 1) - static_cast<LengthType>(vDiff < -1);
		    if (hDiff != 0)
			{
			    follower.x += static_cast<LengthType>(hDiff > 0) - static_cast<LengthType>(hDiff < 0);
		    };
		    continue;
	    }

	    if (std::abs(hDiff) > 1)
		{
		    follower.x += static_cast<LengthType>(hDiff > 1) - static_cast<LengthType>(hDiff < -1);
		    if (vDiff != 0)
			{
			    follower.y += static_cast<LengthType>(vDiff > 0) - static_cast<LengthType>(vDiff < 0);
		    };
		    continue;
	    }
	}
}

template class Rope<LengthType_t, DistType_t, ShortRopeLength>;
template class Rope<LengthType_t, DistType_t, LongRopeLength>;
} // namespace Solutions::RopeBridge