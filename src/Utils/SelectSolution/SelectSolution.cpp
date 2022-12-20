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
    if (day == 1) {
	    if (problem == 1) {
		    return FattestElfCalories;
		}
	    if (problem == 2) {
		    return TopThreeFattestElfCalories;
		}
	}
    if (day == 2) {
	    if (problem == 1) {
		    return RockPaperScissors;
		}
	    if (problem == 2) {
		    return DecryptedRockPaperScissors;
		}
	}
    if (day == 3) {
	    if (problem == 1) {
		    return RucksackReorganization;
		}
	    if (problem == 2) {
		    return RucksackBadges;
		}
	}
    if (day == 4) {
	    if (problem == 1) {
		    return CampCleanup;
		}
	    if (problem == 2) {
		    return PartialCampCleanup;
		}
	}

    return Invalid;
}

// Workaround for re-using same data for different solutions
auto
SelectSolutionData(SolutionId solutionId) -> SolutionId
{
    using enum SolutionId;
    switch (solutionId) {
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
	    case Invalid:
		{
		    return Invalid;
		}
	}
}

} // namespace utils
