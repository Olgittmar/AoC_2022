#include "RuckSack.hpp"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <exception>
#include <iostream>
#include <numeric>
#include <string_view>
#include <vector>

namespace {

class RuckSack
{
    public:

	explicit RuckSack(const std::string_view& data)
	{
	    const auto dataLength = data.length();
	    m_compartmentA = std::string(data.substr(0, dataLength / 2));
	    m_compartmentB = std::string(data.substr(dataLength / 2, std::string_view::npos));

	    calculatePriority();
	}

	void
	calculatePriority()
	{
	    std::ranges::sort(m_compartmentA.begin(), m_compartmentA.end());
	    std::ranges::sort(m_compartmentB.begin(), m_compartmentB.end());

	    std::string intersection;
	    std::ranges::set_intersection(m_compartmentA, m_compartmentB, &intersection);

	    constexpr auto charToPriority = [](char character) -> uint32_t
	    {
		constexpr auto uppercaseOffset = 26U;
		const auto islowercase = static_cast<unsigned int>(std::islower(character) != 0);
		const auto isuppercase = static_cast<unsigned int>(std::isupper(character) != 0);
		return islowercase * uint32_t(character - 'a') +
		       isuppercase * (uint32_t(character - 'A') + uppercaseOffset) + 1U;
	    };

	    // Accumulate by char value
	    m_priority = std::accumulate(intersection.cbegin(), intersection.cend(), 0U,
					 [&charToPriority](uint32_t sum, char character) -> uint32_t
					 { return sum + charToPriority(character); });
	}

	auto
	getPriority() const -> uint32_t
	{
	    return m_priority;
	}

    private:

	std::string m_compartmentA;
	std::string m_compartmentB;
	uint32_t m_priority{};
};

auto
parseInput(const std::string_view& input) -> std::vector<RuckSack>
{
    std::vector<RuckSack> _ret;
    constexpr auto delimiter = '\n';
    const auto numLines = std::count(input.cbegin(), input.cend(), delimiter) + 1;
    _ret.reserve(numLines);
    // Parse lines
    size_t pos = 0;

    while (pos < input.size()) {
	    const auto nextPos = input.find(delimiter, pos);
	    const auto line = input.substr(pos, nextPos - pos);
	    pos = nextPos + size_t(nextPos != std::string_view::npos);

	    _ret.emplace_back(line);
	}

    return _ret;
}
} // namespace

namespace Solutions {

auto
GetSumOfCompartmentItemTypePriority(const std::string_view& input, bool& success) -> uint32_t
{
    uint32_t sum = 0;
    try {
	    const auto ruckSacks = parseInput(input);
	    sum = std::accumulate(ruckSacks.cbegin(), ruckSacks.cend(), 0U,
				  [](uint32_t sum, const RuckSack& ruckSack) -> uint32_t
				  { return sum + ruckSack.getPriority(); });
	    success = true;
    } catch (const std::exception& err) {
	    std::cout << err.what() << std::endl;
    } catch (...) {
	    std::cout << "Unhandled exception!" << std::endl;
    }

    return sum;
}

} // namespace Solutions