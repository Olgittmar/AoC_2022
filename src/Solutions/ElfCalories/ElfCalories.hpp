#ifndef SOLUTIONS_ELFCALORIES_ELFCALORIES_HPP
#define SOLUTIONS_ELFCALORIES_ELFCALORIES_HPP

#include <string_view>

namespace Solutions {

auto GetCaloriesOfElfWithMostCalories(std::string_view input, bool& success) -> std::uint32_t;
auto GetCaloriesOfTopThreeElvesWithMostCalories(std::string_view input, bool& success) -> std::uint32_t;

} // namespace Solutions
#endif