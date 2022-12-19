#include "RunSolution.hpp"

#include "ElfCalories.hpp"
#include "RockPaperScissors.hpp"
#include "RuckSack.hpp"

#include <string>

namespace Solutions {
auto
runSolution(utils::SolutionId solutionId, const std::string_view& input, bool& success) -> std::string
{
    using enum utils::SolutionId;
    switch (solutionId) {
	    case FattestElfCalories:
		{
		    const auto calories = Solutions::GetCaloriesOfElfWithMostCalories(input, success);
		    return std::to_string(calories);
		}
	    case TopThreeFattestElfCalories:
		{
		    const auto calories = Solutions::GetCaloriesOfTopThreeElvesWithMostCalories(input, success);
		    return std::to_string(calories);
		}
	    case RockPaperScissors:
		{
		    const auto score = Solutions::GetScoreOfStrategyGuide(input, success);
		    return std::to_string(score);
		}
	    case DecryptedRockPaperScissors:
		{
		    const auto score = Solutions::GetScoreOfDecryptedStrategyGuide(input, success);
		    return std::to_string(score);
		}
	    case RucksackReorganization:
		{
		    const auto sum = Solutions::GetSumOfCompartmentItemTypePriority(input, success);
		    return std::to_string(sum);
		}
	    case Invalid:
		{
		    return "Invalid solutionId";
		}
	}
}
} // namespace Solutions