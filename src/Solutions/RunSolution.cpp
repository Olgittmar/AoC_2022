#include "RunSolution.hpp"

#include "ElfCalories.hpp"
#include "RockPaperScissors.hpp"

namespace Solutions {
auto
runSolution(utils::SolutionId solutionId, const std::string_view& input, bool& success) -> uint32_t
{
    using enum utils::SolutionId;
    switch (solutionId) {
	    case FattestElfCalories:
		{
		    const auto calories = Solutions::GetCaloriesOfElfWithMostCalories(input, success);
		    return calories;
		}
	    case TopThreeFattestElfCalories:
		{
		    const auto calories = Solutions::GetCaloriesOfTopThreeElvesWithMostCalories(input, success);
		    return calories;
		}
	    case RockPaperScissors:
		{
		    const auto score = Solutions::GetScoreOfStrategyGuide(input, success);
		    return score;
		}
	    case DecryptedRockPaperScissors:
		{
		    const auto score = Solutions::GetScoreOfDecryptedStrategyGuide(input, success);
		    return score;
		}
	    case Invalid:
		{
		    return 0;
		}
	}
}
} // namespace Solutions