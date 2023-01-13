#ifndef SOLUTIONS_SUPPLYSTACKS_HPP
#define SOLUTIONS_SUPPLYSTACKS_HPP

#include <cstddef>
#include <string>
#include <string_view>

namespace Solutions {

constexpr size_t numStacksInDataSet = 9UL;
constexpr size_t numStacksInTestDataSet = 3UL;

template<size_t NumStacksInSupply>
auto GetCratesAtTopOfStacksAfterMoveOperations(const std::string_view& input, bool& success) -> std::string;

template<size_t NumStacksInSupply>
auto GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane(const std::string_view& input, bool& success)
  -> std::string;

} // namespace Solutions
#endif