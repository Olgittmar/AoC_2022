#ifndef SOLUTIONS_RUCKSACK_HPP
#define SOLUTIONS_RUCKSACK_HPP

#include <string_view>

namespace Solutions {

auto GetSumOfCompartmentItemTypePriority(const std::string_view& input, bool& success) -> std::uint32_t;
auto GetSumOfAuthenticityBadges(const std::string_view& input, bool& success) -> std::uint32_t;

} // namespace Solutions
#endif