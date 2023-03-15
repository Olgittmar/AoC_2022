#include "RopeBridge.hpp"

#include "PrettyPrint/PrettyPrint.hpp"
#include "Rope.hpp"

#include <cstddef>
#include <unordered_set>
#include <vector>

namespace Solutions {

auto
GetNumPositionsVisitedByTail(const std::string_view& input, bool& success) -> size_t
{
    using Rope = RopeBridge::Rope<RopeBridge::LengthType_t, RopeBridge::DistType_t>;

    constexpr auto lineDelim = '\n';
    size_t _ret = 0;
    std::unordered_set<Rope::Position_t, RopeBridge::PositionHash_t> tailPosHistory;
    Rope rope;

    // Pos here means the position in the input, not in rope coordinates
    size_t startPos = 0;
    while (startPos < input.size())
	{
	    const auto endPos = input.find(lineDelim, startPos);
	    const auto line = input.substr(startPos, endPos - startPos);
	    auto& out = utils::log(std::experimental::source_location::current(), "line: ", line, '\n');
	    startPos = endPos + 1;

	    const auto& motion = Rope::makeMotion(line);

	    for (size_t distMoved = 0; distMoved < motion.distance; ++distMoved)
		{
		    const auto newTailPos = rope.moveHead(motion.direction);
		    const auto headPos = rope.getHeadPos();
		    out << "headPos: {" << headPos.x << ',' << headPos.y << "}";

		    const auto alreadyVisited = tailPosHistory.contains(newTailPos);
		    if (!alreadyVisited)
			{
			    tailPosHistory.insert(newTailPos);
			    out << ", newTailPos: {" << newTailPos.x << ',' << newTailPos.y << "}";
		    }
		    out << std::endl;
		}
	}

    _ret = tailPosHistory.size();

    {
	auto& out = utils::log(std::experimental::source_location::current(), "history: ");
	for (const auto& item : tailPosHistory)
	    {
		out << "{" << item.x << ", " << item.y << "}" << std::endl;
	    }
    }

    success = true;
    return _ret;
}

// Solution template instantiations
// template auto GetNumPositionsVisitedByTail<>(const std::string_view& input, bool& success) -> size_t;

} // namespace Solutions