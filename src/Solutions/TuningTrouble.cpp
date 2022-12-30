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
#include <string_view>

namespace {
template<size_t SizeOfMarker>
auto
getMarkerEndPos(const std::string_view& data) -> std::uint32_t
{
    constexpr auto duplicateCharsFound = [](const std::string_view& subStr) -> bool
    {
	const auto numDuplicates = std::ranges::count_if(subStr, [&subStr](char character)
							 { return !(1 == std::ranges::count(subStr, character)); });

	return (0 < numDuplicates);
    };

    uint32_t beforeSequencePos = SizeOfMarker;

    while (beforeSequencePos < data.size())
	{
	    // take a span of SizeOfMarker chars from the buffer
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
GetNumCharactersBeforeStartOfPacket(const std::string_view& input, bool& success) -> std::uint32_t
{
    constexpr size_t numCharsInStartOfPacketMarker = 4UL;
    uint32_t _ret = 0;

    try
	{
	    _ret = getMarkerEndPos<numCharsInStartOfPacketMarker>(input);

	    success = (_ret != input.size());
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
    } catch (...)
	{
	    std::cout << "Unhandled exception!" << std::endl;
    }
    return _ret;
}

auto
GetNumCharactersBeforeStartOfMessage(const std::string_view& input, bool& success) -> std::uint32_t
{
    constexpr size_t numCharsInStartOfMessageMarker = 14UL;
    uint32_t _ret = 0;

    try
	{
	    _ret = getMarkerEndPos<numCharsInStartOfMessageMarker>(input);

	    success = (_ret != input.size());
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
    } catch (...)
	{
	    std::cout << "Unhandled exception!" << std::endl;
    }
    return _ret;
}

} // namespace Solutions