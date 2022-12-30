#include "SelectSolution.hpp"

#include "Definitions.hpp"

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

auto
SelectSolution(uint32_t day, uint32_t problem) -> SolutionId
{
    using enum SolutionId;
    switch (day)
	{
	    case 1:
		{
		    if (problem == 1)
			{
			    return FattestElfCalories;
		    }
		    if (problem == 2)
			{
			    return TopThreeFattestElfCalories;
		    }
		}
	    case 2:
		{
		    if (problem == 1)
			{
			    return RockPaperScissors;
		    }
		    if (problem == 2)
			{
			    return DecryptedRockPaperScissors;
		    }
		}
	    case 3:
		{
		    if (problem == 1)
			{
			    return RucksackReorganization;
		    }
		    if (problem == 2)
			{
			    return RucksackBadges;
		    }
		}
	    case 4:
		{
		    if (problem == 1)
			{
			    return CampCleanup;
		    }
		    if (problem == 2)
			{
			    return PartialCampCleanup;
		    }
		}
	    case 5: // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
		{
		    if (problem == 1)
			{
			    return RearrangeSupplyStacks;
		    }
		    if (problem == 2)
			{
			    return RearrangeSupplyStacksWithAdvancedCrane;
		    }
		}
	    case 6: // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
		{
		    if (problem == 1)
			{
			    return TuningTrouble;
		    }
		    if (problem == 2)
			{
			    return MessageTuningTrouble;
		    }
		}
	    default:
		return Invalid;
	}
}

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
	    case Invalid:
		{
		    return Invalid;
		}
	}
}

} // namespace utils
