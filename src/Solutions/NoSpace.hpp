#ifndef SOLUTIONS_NOSPACE_HPP
#define SOLUTIONS_NOSPACE_HPP

#include <string_view>

namespace Solutions {

auto GetTotalSizeOfDirectories(const std::string_view& input, bool& success) -> std::uint32_t;

} // namespace Solutions
#endif