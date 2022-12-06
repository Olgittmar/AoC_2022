#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// Project wide definitions
#include <string_view>
namespace utils {

constexpr int daysSolved = 1;
constexpr int problemsPerDay = 2;

enum class SolutionId : uint32_t
{
    FattestElfCalories = 1,
    TopThreeFattestElfCalories = 2,
    Invalid = 0
};

namespace SolutionIdStrings {
    constexpr auto FattestElfCalories = "FattestElfCalories";
} // namespace SolutionIdStrings

constexpr auto
SolutionIdToString(SolutionId solutionId) -> std::string_view
{
    switch (solutionId) {
	    case SolutionId::FattestElfCalories:
		{
		    return SolutionIdStrings::FattestElfCalories;
		}
	    case SolutionId::TopThreeFattestElfCalories:
		{
		    return SolutionIdStrings::FattestElfCalories;
		}
	    case SolutionId::Invalid:
		{
		    return "";
		}
	}
}

} // namespace utils

#endif