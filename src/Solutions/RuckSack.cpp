#include "RuckSack.hpp"

#include <algorithm>
#include <bits/ranges_algo.h>
#include <bits/ranges_util.h>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <iterator>
#include <numeric>
#include <span>
#include <string_view>
#include <type_traits>
#include <vector>

namespace {

constexpr size_t numRucksacksInGroup = 3;

class RuckSack
{
    public:

	RuckSack() = default;
	explicit RuckSack(const std::string_view& data) : m_ruckSackContents{data.begin(), data.end()} {}

	static constexpr auto
	charToPriority(char character) -> uint32_t
	{
	    constexpr auto uppercaseOffset = 26U;
	    const auto islowercase = static_cast<unsigned int>(std::islower(character) != 0);
	    const auto isuppercase = static_cast<unsigned int>(std::isupper(character) != 0);
	    return islowercase * uint32_t(character - 'a') +
		   isuppercase * (uint32_t(character - 'A') + uppercaseOffset) + 1U;
	};

	void
	calculatePriority()
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

	auto
	getPriority() const -> uint32_t
	{
	    return m_priority;
	}

	auto
	getContents() const -> std::string
	{
	    return m_ruckSackContents;
	}

    private:

	std::string m_ruckSackContents{};
	uint32_t m_priority{};
};

template<size_t N> class RuckSackGroup
{
    public:

	// Use range as parameter instead?
	explicit RuckSackGroup(const std::vector<RuckSack>::const_iterator& start,
			       const std::vector<RuckSack>::const_iterator& stop)
	{
	    m_contents.reserve(N);
	    std::ranges::for_each(start, stop,
				  [this](const RuckSack& ruckSack)
				  {
				      auto& contents = m_contents.emplace_back(ruckSack.getContents());
				      std::ranges::sort(contents);
				      const auto last = std::unique(contents.begin(), contents.end());
				      contents.erase(last, contents.end());
				  });
	}

	[[nodiscard]] auto
	getPriorityOfAuthenticityBadge() const -> uint32_t
	{
	    std::string from_intersection = m_contents.front();

	    std::ranges::for_each(std::next(m_contents.begin()), m_contents.end(),
				  [&from_intersection](const std::string& nextContents)
				  {
				      std::string to_intersection;
				      std::ranges::set_intersection(from_intersection, nextContents,
								    std::back_inserter(to_intersection));
				      from_intersection = to_intersection;
				  });

	    if (from_intersection.size() != 1)
		{
		    std::cout << "Warning, unexpected intersection size: " << from_intersection.size() << std::endl;
	    }

	    return RuckSack::charToPriority(from_intersection.front());
	}

    private:

	// Generalize for arbitrary grouping
	std::vector<std::string> m_contents{};
};

auto
parseInput(const std::string_view& input) -> std::vector<RuckSack>
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

auto
parseInputAsGroups(const std::string_view& input) -> std::vector<RuckSackGroup<numRucksacksInGroup>>
{
    std::vector<RuckSackGroup<numRucksacksInGroup>> _ret;
    const auto ruckSacks = parseInput(input);

    auto ruckSack = ruckSacks.begin();
    while (ruckSack != ruckSacks.end())
	{
	    auto nextRuckSack = std::next(ruckSack, numRucksacksInGroup);
	    _ret.emplace_back(ruckSack, nextRuckSack);
	    ruckSack = nextRuckSack;
	}

    return _ret;
}

} // namespace

namespace Solutions {

auto
GetSumOfCompartmentItemTypePriority(const std::string_view& input, bool& success) -> uint32_t
{
    uint32_t sum = 0;

    const auto ruckSacks = parseInput(input);
    sum =
      std::accumulate(ruckSacks.cbegin(), ruckSacks.cend(), 0U,
		      [](uint32_t sum, const RuckSack& ruckSack) -> uint32_t { return sum + ruckSack.getPriority(); });
    success = true;

    return sum;
}

auto
GetSumOfAuthenticityBadges(const std::string_view& input, bool& success) -> std::uint32_t
{
    uint32_t sum = 0;

    const auto ruckSackGroups = parseInputAsGroups(input);
    sum = std::accumulate(ruckSackGroups.begin(), ruckSackGroups.end(), 0U,
			  [](uint32_t sum, const RuckSackGroup<numRucksacksInGroup>& ruckSackGroup)
			  { return sum + ruckSackGroup.getPriorityOfAuthenticityBadge(); });
    success = true;

    return sum;
}

} // namespace Solutions