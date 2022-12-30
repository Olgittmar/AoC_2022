#ifndef UTILS_RUNSOLUTION_RUNSOLUTION_HPP
#define UTILS_RUNSOLUTION_RUNSOLUTION_HPP

// utils
#include <Utils.hpp>

// Internal
#include "CampCleanup.hpp"
#include "ElfCalories.hpp"
#include "RockPaperScissors.hpp"
#include "RuckSack.hpp"
#include "SupplyStacks.hpp"
#include "TuningTrouble.hpp"

// Std
#include <string>

namespace Solutions {

template<bool testRun = false>
auto
runSolution(utils::SolutionId solutionId, const std::string_view& input, bool& success) -> std::string
{
    using enum utils::SolutionId;
    switch (solutionId)
	{
	    case FattestElfCalories:
		{
		    const auto calories = GetCaloriesOfElfWithMostCalories(input, success);
		    return std::to_string(calories);
		}
	    case TopThreeFattestElfCalories:
		{
		    const auto calories = GetCaloriesOfTopThreeElvesWithMostCalories(input, success);
		    return std::to_string(calories);
		}
	    case RockPaperScissors:
		{
		    const auto score = GetScoreOfStrategyGuide(input, success);
		    return std::to_string(score);
		}
	    case DecryptedRockPaperScissors:
		{
		    const auto score = GetScoreOfDecryptedStrategyGuide(input, success);
		    return std::to_string(score);
		}
	    case RucksackReorganization:
		{
		    const auto sum = GetSumOfCompartmentItemTypePriority(input, success);
		    return std::to_string(sum);
		}
	    case RucksackBadges:
		{
		    const auto sum = GetSumOfAuthenticityBadges(input, success);
		    return std::to_string(sum);
		}
	    case CampCleanup:
		{
		    const auto sum = GetNumRedundantAssignmentPairs(input, success);
		    return std::to_string(sum);
		}
	    case PartialCampCleanup:
		{
		    const auto sum = GetNumPartiallyRedundantAssignmentPairs(input, success);
		    return std::to_string(sum);
		}
	    case RearrangeSupplyStacks:
		{
		    const auto crateIds = GetCratesAtTopOfEachStack<testRun>(input, success);
		    return crateIds;
		}
	    case RearrangeSupplyStacksWithAdvancedCrane:
		{
		    const auto crateIds = GetCratesAtTopOfEachStackWithAdvancedCrane<testRun>(input, success);
		    return crateIds;
		}
	    case TuningTrouble:
		{
		    const auto numChars = GetNumCharactersBeforeStartOfPacket(input, success);
		    return std::to_string(numChars);
		}
	    case Invalid:
		{
		    return "runSolution(): Invalid solutionId";
		}
	}
}

} // namespace Solutions
#endif