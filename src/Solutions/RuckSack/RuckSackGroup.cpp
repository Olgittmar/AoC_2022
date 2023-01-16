#include "RuckSackGroup.hpp"

// Std
#include <algorithm>
#include <iostream>
#include <ranges>

// Internal
#include "Definitions.hpp"

namespace Solutions::CheckRuckSacks {

template<size_t NumSacksInGroup>
RuckSackGroup<NumSacksInGroup>::RuckSackGroup(const std::vector<RuckSack>::const_iterator& start,
					      const std::vector<RuckSack>::const_iterator& stop)
{
    m_contents.reserve(NumSacksInGroup);
    std::ranges::for_each(start, stop,
			  [this](const RuckSack& ruckSack)
			  {
			      auto& contents = m_contents.emplace_back(ruckSack.getContents());
			      std::ranges::sort(contents);
			      const auto last = std::unique(contents.begin(), contents.end());
			      contents.erase(last, contents.end());
			  });
}

template<size_t NumSacksInGroup>
[[nodiscard]] auto
RuckSackGroup<NumSacksInGroup>::getPriorityOfAuthenticityBadge() const -> uint32_t
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

template<size_t NumSacksInGroup>
auto
stringToRuckSackGroups(const std::string_view& input) -> std::vector<RuckSackGroup<NumSacksInGroup>>
{
    std::vector<RuckSackGroup<NumSacksInGroup>> _ret;
    const auto ruckSacks = stringToRuckSacks(input);

    auto ruckSack = ruckSacks.begin();
    while (ruckSack != ruckSacks.end())
	{
	    auto nextRuckSack = std::next(ruckSack, NumSacksInGroup);
	    _ret.emplace_back(ruckSack, nextRuckSack);
	    ruckSack = nextRuckSack;
	}

    return _ret;
}

template class RuckSackGroup<CheckRuckSacks::numRucksacksInGroup>;

template auto stringToRuckSackGroups<CheckRuckSacks::numRucksacksInGroup>(const std::string_view& input)
  -> std::vector<RuckSackGroup<CheckRuckSacks::numRucksacksInGroup>>;

} // namespace Solutions::CheckRuckSacks