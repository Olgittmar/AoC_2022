#include "TuningTrouble.hpp"

// Std
#include <algorithm>
#include <bits/ranges_algo.h>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <iterator>
#include <ranges>
#include <set>
#include <string_view>

namespace {
template<size_t SizeOfMarker>
auto
getMarkerEndPos(std::string_view data) -> std::uint32_t
{
    constexpr auto duplicateCharsFound = [](std::string_view subStr) -> bool
    {
	std::string tmp(subStr);
	std::ranges::sort(tmp);
	const auto [first, last] = std::ranges::unique(tmp);
	tmp.erase(first, last);
	return subStr.size() > tmp.size();
    };

    uint32_t beforeSequencePos = SizeOfMarker;

    while (beforeSequencePos < data.size())
	{
	    // slide_view in c++23
	    const auto sequence = data.substr(beforeSequencePos - SizeOfMarker, SizeOfMarker);

	    if (!duplicateCharsFound(sequence))
		{
		    return beforeSequencePos;
	    }

	    ++beforeSequencePos;
	}

    return data.size();
}

} // namespace

namespace Solutions {

auto
GetNumCharactersBeforeStartOfPacket(std::string_view input, bool& success) -> std::uint32_t
{
    constexpr size_t numCharsInStartOfPacketMarker = 4UL; // TODO: Move to template arg
    const auto _ret = getMarkerEndPos<numCharsInStartOfPacketMarker>(input);

    success = (_ret != input.size());

    return _ret;
}

auto
GetNumCharactersBeforeStartOfMessage(std::string_view input, bool& success) -> std::uint32_t
{
    constexpr size_t numCharsInStartOfMessageMarker = 14UL; // TODO: Same as above
    const auto _ret = getMarkerEndPos<numCharsInStartOfMessageMarker>(input);

    success = (_ret != input.size());

    return _ret;
}

} // namespace Solutions