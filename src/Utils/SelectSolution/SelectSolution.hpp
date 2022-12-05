#ifndef UTILS_SELECTSOLUTION_SELECTSOLUTION_HPP
#define UTILS_SELECTSOLUTION_SELECTSOLUTION_HPP

#include <Definitions.hpp>

#include <string_view>

namespace utils {

auto SelectSolution(int day, int problem) -> SolutionId;

} // namespace utils
#endif