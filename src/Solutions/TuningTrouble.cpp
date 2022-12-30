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
// Implementation specific to this days problem
} // namespace

namespace Solutions {

auto
GetNumCharactersBeforeStartOfPacket(const std::string_view& input, bool& success) -> std::uint32_t
{
    constexpr auto duplicateCharsFound = [](const std::string_view& subStr) -> bool
    {
	if (subStr.size() < 4)
	    {
		return false;
	}

	const auto first = subStr.at(0);
	const auto second = subStr.at(1);
	const auto third = subStr.at(2);

	const auto firstIsUnique = (1 == std::ranges::count(subStr, first));
	const auto secondIsUnique = (1 == std::ranges::count(subStr, second));
	const auto thirdIsUnique = (1 == std::ranges::count(subStr, third));

	return !(firstIsUnique && secondIsUnique && thirdIsUnique);
    };

    uint32_t _ret = 0;

    try
	{
	    uint32_t beforeSequencePos = 4;

	    while (beforeSequencePos < input.size())
		{
		    // take a span of 4 chars from the buffer
		    const auto sequence = input.substr(beforeSequencePos - 4, 4);

		    if (!duplicateCharsFound(sequence))
			{
			    _ret = beforeSequencePos;
			    break;
		    }

		    ++beforeSequencePos;
		}

	    success = true;
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