#include "RopeBridge.hpp"

#include "Definitions.hpp"
#include "PrettyPrint/PrettyPrint.hpp"
#include "Rope.hpp"

#include <cstddef>
#include <unordered_set>
#include <vector>

namespace Solutions {

template<size_t RopeLength>
auto
GetNumPositionsVisitedByTail(std::string_view input, bool& success) -> size_t
{
    using Rope_t = RopeBridge::Rope<RopeBridge::LengthType_t, RopeBridge::DistType_t, RopeLength>;

    constexpr auto lineDelim = '\n';
    size_t _ret = 0;
    std::unordered_set<typename Rope_t::Position_t, RopeBridge::PositionHash_t> tailPosHistory;
    Rope_t rope;

    // Pos here means the position in the input, not in rope coordinates
    size_t startPos = 0;
    while (startPos < input.size())
	{
	    const auto endPos = input.find(lineDelim, startPos);
	    const auto line = input.substr(startPos, endPos - startPos);
	    startPos = endPos + 1;

	    const auto& motion = Rope_t::makeMotion(line);

	    for (size_t distMoved = 0; distMoved < motion.distance; ++distMoved)
		{
		    const auto newTailPos = rope.moveHead(motion.direction);
		    tailPosHistory.insert(newTailPos);
		}
	}

    _ret = tailPosHistory.size();

    success = true;
    return _ret;
}

// Solution template instantiations
template auto GetNumPositionsVisitedByTail<RopeBridge::ShortRopeLength>(std::string_view input, bool& success) -> size_t;

template auto GetNumPositionsVisitedByTail<RopeBridge::LongRopeLength>(std::string_view input, bool& success) -> size_t;

} // namespace Solutions