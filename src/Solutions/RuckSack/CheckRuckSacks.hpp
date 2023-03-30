#ifndef SOLUTIONS_RUCKSACK_CHECKRUCKSACKS_HPP
#define SOLUTIONS_RUCKSACK_CHECKRUCKSACKS_HPP

#include <string_view>

namespace Solutions {

auto GetSumOfCompartmentItemTypePriority(std::string_view input, bool& success) -> std::uint32_t;
auto GetSumOfAuthenticityBadges(std::string_view input, bool& success) -> std::uint32_t;

} // namespace Solutions
#endif