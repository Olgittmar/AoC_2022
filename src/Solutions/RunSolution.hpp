#ifndef UTILS_RUNSOLUTION_RUNSOLUTION_HPP
#define UTILS_RUNSOLUTION_RUNSOLUTION_HPP

// Internal
#include <Utils.hpp>
// Std
#include <string>

namespace Solutions {

auto runSolution(utils::SolutionId solutionId, const std::string_view& input, bool& success) -> uint32_t;

} // namespace Solutions
#endif