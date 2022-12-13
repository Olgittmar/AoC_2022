#ifndef UTILS_SELECTSOLUTION_SELECTSOLUTION_HPP
#define UTILS_SELECTSOLUTION_SELECTSOLUTION_HPP

#include <Definitions.hpp>
#include <string_view>

namespace utils {

auto SelectSolution(uint32_t day, uint32_t problem) -> SolutionId;
// Workaround for reusing same data for multiple tests without having the same name correlated to the enum
auto SelectSolutionData(SolutionId) -> SolutionId;

} // namespace utils
#endif