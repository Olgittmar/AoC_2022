#ifndef UTILS_SELECTSOLUTION_SELECTSOLUTION_HPP
#define UTILS_SELECTSOLUTION_SELECTSOLUTION_HPP

#include <Definitions.hpp>
#include <string_view>

namespace utils {

constexpr auto
SelectSolution(uint32_t day, uint32_t problem) -> SolutionId
{
    const auto _tmp = dayAndProblemToComposite(day, problem);

    if (!IsValidSolution::valueExists(_tmp))
	{
	    return SolutionId::Invalid;
    }

    return SolutionId(_tmp);
}

// Workaround for reusing same data for multiple tests without having the same name correlated to the enum
auto SelectSolutionData(SolutionId) -> SolutionId;

} // namespace utils
#endif