#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// Project wide definitions
#include <string_view>
namespace utils {

constexpr int daysSolved = 2;
constexpr int problemsPerDay = 2;

enum class SolutionId : uint32_t
{
    FattestElfCalories = 1,
    TopThreeFattestElfCalories = 2,
    RockPaperScissors = 3,
    Invalid = 0
};

namespace SolutionIdStrings {
    constexpr auto FattestElfCalories = "FattestElfCalories";
    constexpr auto RockPaperScissors = "RockPaperScissors";
} // namespace SolutionIdStrings

constexpr auto
SolutionIdToString(SolutionId solutionId) -> std::string_view
{
    switch (solutionId) {
	    case SolutionId::FattestElfCalories:
	    case SolutionId::TopThreeFattestElfCalories:
		{
		    return SolutionIdStrings::FattestElfCalories;
		}
	    case SolutionId::RockPaperScissors:
		{
		    return SolutionIdStrings::RockPaperScissors;
		}
	    case SolutionId::Invalid:
		{
		    return "";
		}
	}
}

} // namespace utils

#endif