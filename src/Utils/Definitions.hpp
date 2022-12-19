#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// Project wide definitions
#include <string_view>
namespace utils {

constexpr int daysSolved = 3;
constexpr int problemsPerDay = 2;

enum class SolutionId : uint32_t
{
    FattestElfCalories = 1,
    TopThreeFattestElfCalories = 2,
    RockPaperScissors = 3,
    DecryptedRockPaperScissors = 4,
    RucksackReorganization = 5,
    Invalid = 0
};

namespace SolutionIdStrings {
    constexpr auto FattestElfCalories = "FattestElfCalories";
    constexpr auto TopThreeFattestElfCalories = "TopThreeFattestElfCalories";
    constexpr auto RockPaperScissors = "RockPaperScissors";
    constexpr auto DecryptedRockPaperScissors = "DecryptedRockPaperScissors";
    constexpr auto RucksackReorganization = "RucksackReorganization";
    constexpr auto Invalid = "InvalidSolutionId";
} // namespace SolutionIdStrings

constexpr auto
SolutionIdToString(SolutionId solutionId) noexcept -> const char*
{
    switch (solutionId) {
	    case SolutionId::FattestElfCalories:
		{
		    return SolutionIdStrings::FattestElfCalories;
		}
	    case SolutionId::TopThreeFattestElfCalories:
		{
		    return SolutionIdStrings::TopThreeFattestElfCalories;
		}
	    case SolutionId::RockPaperScissors:
		{
		    return SolutionIdStrings::RockPaperScissors;
		}
	    case SolutionId::DecryptedRockPaperScissors:
		{
		    return SolutionIdStrings::DecryptedRockPaperScissors;
		}
	    case SolutionId::RucksackReorganization:
		{
		    return SolutionIdStrings::RucksackReorganization;
		}
	    case SolutionId::Invalid:
		{
		    return SolutionIdStrings::Invalid;
		}
	}
}

} // namespace utils

#endif