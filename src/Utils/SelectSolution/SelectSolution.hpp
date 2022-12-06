#ifndef UTILS_SELECTSOLUTION_SELECTSOLUTION_HPP
#define UTILS_SELECTSOLUTION_SELECTSOLUTION_HPP

#include <Definitions.hpp>
#include <string_view>

namespace utils {

auto SelectSolution(uint32_t day, uint32_t problem) -> SolutionId;

} // namespace utils
#endif