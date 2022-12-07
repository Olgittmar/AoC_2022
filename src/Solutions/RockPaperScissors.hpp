#ifndef SOLUTIONS_ROCKPAPERSCISSORS_HPP
#define SOLUTIONS_ROCKPAPERSCISSORS_HPP

#include <string_view>

namespace Solutions {

auto GetScoreOfStrategyGuide(const std::string_view& input, bool& success) -> uint32_t;
auto GetScoreOfDecryptedStrategyGuide(const std::string_view& input, bool& success) -> uint32_t;

} // namespace Solutions
#endif