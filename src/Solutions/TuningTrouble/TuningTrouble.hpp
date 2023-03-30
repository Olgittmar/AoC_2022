#ifndef SOLUTIONS_TUNINGTROUBLE_TUNINGTROUBLE_HPP
#define SOLUTIONS_TUNINGTROUBLE_TUNINGTROUBLE_HPP

#include <string_view>

namespace Solutions {

auto GetNumCharactersBeforeStartOfPacket(std::string_view input, bool& success) -> std::uint32_t;
auto GetNumCharactersBeforeStartOfMessage(std::string_view input, bool& success) -> std::uint32_t;

} // namespace Solutions
#endif