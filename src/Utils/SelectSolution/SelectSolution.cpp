#include "SelectSolution.hpp"

#include "Definitions.hpp"

#include <cstdint>
#include <stdexcept>
#include <string>

namespace {
auto
toErrorFormat(uint32_t day, uint32_t problem) -> std::string
{
    return std::string("day: ") + std::to_string(day) + " problem: " + std::to_string(problem);
}
} // namespace
namespace utils {

// Workaround for re-using same data for different solutions
auto
SelectSolutionData(SolutionId solutionId) -> SolutionId
{
    using enum SolutionId;
    switch (solutionId)
	{
	    case FattestElfCalories:
	    case TopThreeFattestElfCalories:
		{
		    return FattestElfCalories;
		}
	    case RockPaperScissors:
	    case DecryptedRockPaperScissors:
		{
		    return RockPaperScissors;
		}
	    case RucksackReorganization:
	    case RucksackBadges:
		{
		    return RucksackReorganization;
		}
	    case CampCleanup:
	    case PartialCampCleanup:
		{
		    return CampCleanup;
		}
	    case RearrangeSupplyStacks:
	    case RearrangeSupplyStacksWithAdvancedCrane:
		{
		    return RearrangeSupplyStacks;
		}
	    case TuningTrouble:
	    case MessageTuningTrouble:
		{
		    return TuningTrouble;
		}
	    case NoSpace:
	    case YesSpace:
		{
		    return NoSpace;
		}
	    case Invalid:
		{
		    return Invalid;
		}
	}
}

} // namespace utils
