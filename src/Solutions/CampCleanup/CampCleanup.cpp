#include "CampCleanup.hpp"

// Std
#include <algorithm>
#include <ranges>

// Internal
#include "AssignmentPair.hpp"

namespace Solutions {

auto
GetNumRedundantAssignmentPairs(const std::string_view& input, bool& success) -> std::uint32_t
{
    uint32_t sum = 0;

    const auto assignmentPairs = CampCleanup::stringToAssignmentPairs(input);
    sum = std::ranges::count_if(assignmentPairs,
				[](const CampCleanup::AssignmentPair& pair) { return pair.fullyOverlaps(); });
    success = true;

    return sum;
}

auto
GetNumPartiallyRedundantAssignmentPairs(const std::string_view& input, bool& success) -> std::uint32_t
{
    uint32_t sum = 0;

    const auto assignmentPairs = CampCleanup::stringToAssignmentPairs(input);
    sum = std::ranges::count_if(assignmentPairs,
				[](const CampCleanup::AssignmentPair& pair) { return pair.partiallyOverlaps(); });

    success = true;
    return sum;
}
} // namespace Solutions
