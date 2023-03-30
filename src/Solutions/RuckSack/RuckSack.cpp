#include "RuckSack.hpp"

#include "PrettyPrint/PrettyPrint.hpp"

// Std
#include <algorithm>
#include <bits/ranges_algo.h>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>

namespace Solutions::CheckRuckSacks {

void
RuckSack::calculatePriority()
{
    const auto dataLength = m_ruckSackContents.length();
    std::string compartmentA{m_ruckSackContents.substr(0, dataLength / 2)};
    std::string compartmentB{m_ruckSackContents.substr(dataLength / 2, std::string_view::npos)};

    std::ranges::sort(compartmentA);
    std::ranges::sort(compartmentB);

    std::string intersection{};
    std::ranges::set_intersection(compartmentA, compartmentB, std::back_inserter(intersection));

    auto lastNonDuplicate = std::unique(intersection.begin(), intersection.end());
    intersection.erase(lastNonDuplicate, intersection.end());

    // Accumulate by char value
    m_priority =
      std::accumulate(intersection.cbegin(), intersection.cend(), 0U, [](uint32_t sum, char character) -> uint32_t { return sum + charToPriority(character); });
}

[[nodiscard]] auto
stringToRuckSacks(std::string_view input) -> std::vector<RuckSack>
{
    std::vector<RuckSack> _ret;
    constexpr auto delimiter = '\n';
    const auto numLines = std::ranges::count(input, delimiter);
    _ret.reserve(numLines);

    size_t pos = 0;

    while (pos < input.size())
	{
	    const auto nextPos = input.find(delimiter, pos);
	    const auto line = input.substr(pos, nextPos - pos);
	    pos = nextPos + size_t(nextPos != std::string_view::npos);

	    _ret.emplace_back(line).calculatePriority();
	}

    return _ret;
}

} // namespace Solutions::CheckRuckSacks