#include "RuckSack.hpp"

// Std
#include <algorithm>
#include <numeric>
#include <ranges>

namespace Solutions::CheckRuckSacks {

void
RuckSack::calculatePriority()
{
    const auto dataLength = m_ruckSackContents.length();
    std::string compartmentA{m_ruckSackContents.substr(0, dataLength / 2)};
    std::string compartmentB{m_ruckSackContents.substr(dataLength / 2, std::string_view::npos)};

    std::ranges::sort(compartmentA.begin(), compartmentA.end());
    std::ranges::sort(compartmentB.begin(), compartmentB.end());

    std::string intersection;
    std::ranges::set_intersection(compartmentA, compartmentB, &intersection);

    // Accumulate by char value
    m_priority =
      std::accumulate(intersection.cbegin(), intersection.cend(), 0U,
		      [](uint32_t sum, char character) -> uint32_t { return sum + charToPriority(character); });
}

[[nodiscard]] auto
stringToRuckSacks(const std::string_view& input) -> std::vector<RuckSack>
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