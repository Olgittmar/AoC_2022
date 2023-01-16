#include "CheckRuckSacks.hpp"

// Std
#include <numeric>

// Internal
#include "Definitions.hpp"
#include "RuckSack.hpp"
#include "RuckSackGroup.hpp"

namespace Solutions {

auto
GetSumOfCompartmentItemTypePriority(const std::string_view& input, bool& success) -> uint32_t
{
    uint32_t sum = 0;

    const auto ruckSacks = CheckRuckSacks::stringToRuckSacks(input);
    sum = std::accumulate(ruckSacks.cbegin(), ruckSacks.cend(), 0U,
			  [](uint32_t sum, const CheckRuckSacks::RuckSack& ruckSack) -> uint32_t
			  { return sum + ruckSack.getPriority(); });

    success = true;
    return sum;
}

auto
GetSumOfAuthenticityBadges(const std::string_view& input, bool& success) -> std::uint32_t
{
    uint32_t sum = 0;

    const auto ruckSackGroups = CheckRuckSacks::stringToRuckSackGroups<CheckRuckSacks::numRucksacksInGroup>(input);

    sum = std::accumulate(ruckSackGroups.begin(), ruckSackGroups.end(), 0U,
			  [](uint32_t sum, const auto& ruckSackGroup)
			  { return sum + ruckSackGroup.getPriorityOfAuthenticityBadge(); });

    success = true;
    return sum;
}

} // namespace Solutions