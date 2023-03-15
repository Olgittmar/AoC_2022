#ifndef SOLUTIONS_ROPEBRIDGE_ROPEBRIDGE_HPP
#define SOLUTIONS_ROPEBRIDGE_ROPEBRIDGE_HPP

#include "Utils.hpp"

#include <cstddef>
#include <string_view>

namespace Solutions {

template<size_t RopeLength> auto GetNumPositionsVisitedByTail(const std::string_view& input, bool& success) -> size_t;

} // namespace Solutions
#endif