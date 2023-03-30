#ifndef SOLUTIONS_SUPPLYSTACKS_SUPPLYSTACKS_HPP
#define SOLUTIONS_SUPPLYSTACKS_SUPPLYSTACKS_HPP

#include <cstddef>
#include <string>
#include <string_view>

namespace Solutions {

template<size_t NumStacksInSupply> auto GetCratesAtTopOfStacksAfterMoveOperations(std::string_view input, bool& success) -> std::string;

template<size_t NumStacksInSupply> auto GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane(std::string_view input, bool& success) -> std::string;

} // namespace Solutions
#endif