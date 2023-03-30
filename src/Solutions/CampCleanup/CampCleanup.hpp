#ifndef SOLUTIONS_CAMPCLEANUP_CAMPCLEANUP_HPP
#define SOLUTIONS_CAMPCLEANUP_CAMPCLEANUP_HPP

#include <string_view>

namespace Solutions {

auto GetNumRedundantAssignmentPairs(std::string_view input, bool& success) -> std::uint32_t;
auto GetNumPartiallyRedundantAssignmentPairs(std::string_view input, bool& success) -> std::uint32_t;

} // namespace Solutions
#endif
