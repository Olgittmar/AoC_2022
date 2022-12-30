#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// Project wide definitions
#include <cstdint>
#include <ranges>
#include <string_view>
namespace utils {

enum class SolutionId : uint32_t
{
    FattestElfCalories = 1,
    TopThreeFattestElfCalories = 2,
    RockPaperScissors = 3,
    DecryptedRockPaperScissors = 4,
    RucksackReorganization = 5,
    RucksackBadges = 6,
    CampCleanup = 7,
    PartialCampCleanup = 8,
    RearrangeSupplyStacks = 9,
    RearrangeSupplyStacksWithAdvancedCrane = 10,
    TuningTrouble = 11,
    Invalid = 0
};

namespace SolutionIdStrings {
    constexpr auto FattestElfCalories = "FattestElfCalories";
    constexpr auto TopThreeFattestElfCalories = "TopThreeFattestElfCalories";
    constexpr auto RockPaperScissors = "RockPaperScissors";
    constexpr auto DecryptedRockPaperScissors = "DecryptedRockPaperScissors";
    constexpr auto RucksackReorganization = "RucksackReorganization";
    constexpr auto RucksackBadges = "RucksackBadges";
    constexpr auto CampCleanup = "CampCleanup";
    constexpr auto PartialCampCleanup = "PartialCampCleanup";
    constexpr auto RearrangeSupplyStacks = "RearrangeSupplyStacks";
    constexpr auto RearrangeSupplyStacksWithAdvancedCrane = "RearrangeSupplyStacksWithAdvancedCrane";
    constexpr auto TuningTrouble = "TuningTrouble";
    constexpr auto Invalid = "InvalidSolutionId";
} // namespace SolutionIdStrings

constexpr auto
SolutionIdToString(SolutionId solutionId) noexcept -> const char*
{
    using enum SolutionId;
    switch (solutionId)
	{
	    case FattestElfCalories:
		{
		    return SolutionIdStrings::FattestElfCalories;
		}
	    case TopThreeFattestElfCalories:
		{
		    return SolutionIdStrings::TopThreeFattestElfCalories;
		}
	    case RockPaperScissors:
		{
		    return SolutionIdStrings::RockPaperScissors;
		}
	    case DecryptedRockPaperScissors:
		{
		    return SolutionIdStrings::DecryptedRockPaperScissors;
		}
	    case RucksackReorganization:
		{
		    return SolutionIdStrings::RucksackReorganization;
		}
	    case RucksackBadges:
		{
		    return SolutionIdStrings::RucksackBadges;
		}
	    case CampCleanup:
		{
		    return SolutionIdStrings::CampCleanup;
		}
	    case PartialCampCleanup:
		{
		    return SolutionIdStrings::PartialCampCleanup;
		}
	    case RearrangeSupplyStacks:
		{
		    return SolutionIdStrings::RearrangeSupplyStacks;
		}
	    case RearrangeSupplyStacksWithAdvancedCrane:
		{
		    return SolutionIdStrings::RearrangeSupplyStacksWithAdvancedCrane;
		}
	    case TuningTrouble:
		{
		    return SolutionIdStrings::TuningTrouble;
		}
	    case Invalid:
		{
		    return SolutionIdStrings::Invalid;
		}
	}
}

} // namespace utils

#endif