#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// Project wide definitions
#include <string_view>
namespace utils {

constexpr int daysSolved = 1;
constexpr int problemsPerDay = 2;

enum class SolutionId {
    FattestElfCalories,
    Invalid
};

namespace SolutionIdStrings
{
    constexpr auto FattestElfCalories = "FattestElfCalories";
} // namespace SolutionIdStrings

constexpr auto SolutionIdToString(SolutionId solutionId) -> std::string_view
{
    switch (solutionId) {
	case SolutionId::FattestElfCalories:
        return SolutionIdStrings::FattestElfCalories;
	case SolutionId::Invalid:
	    return "";
    }
}

} // namespace utils

#endif