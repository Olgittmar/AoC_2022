#ifndef SOLUTIONS_ROCKPAPERSCISSORS_ROCKPAPERSCISSORS_HPP
#define SOLUTIONS_ROCKPAPERSCISSORS_ROCKPAPERSCISSORS_HPP

#include <string_view>

namespace Solutions {

auto GetScoreOfStrategyGuide(std::string_view input, bool& success) -> int32_t;
auto GetScoreOfDecryptedStrategyGuide(std::string_view input, bool& success) -> uint32_t;

} // namespace Solutions
#endif