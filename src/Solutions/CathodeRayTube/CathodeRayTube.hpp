#ifndef SOLUTIONS_CATHODERAYTUBE_CATHODERAYTUBE_HPP
#define SOLUTIONS_CATHODERAYTUBE_CATHODERAYTUBE_HPP

#include "Utils.hpp"

#include <cstddef>
#include <string_view>

namespace Solutions {

template<size_t CycleOffset, size_t CycleStep, size_t CycleEnd>
auto GetSumOfSignalStrengths(const std::string_view& input, bool& success) -> long;

} // namespace Solutions
#endif