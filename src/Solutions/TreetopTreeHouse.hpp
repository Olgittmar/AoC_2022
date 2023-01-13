#ifndef SOLUTIONS_TREETOPTREEHOUSE_HPP
#define SOLUTIONS_TREETOPTREEHOUSE_HPP

#include <cstddef>
#include <string_view>

namespace Solutions {

constexpr size_t NumTreeRowsInTest = 5;
constexpr size_t NumTreeColumnsInTest = 5;

constexpr size_t NumTreeRows = 99;
constexpr size_t NumTreeColumns = 99;

template<typename HeightType, size_t Rows, size_t Columns>
auto GetNumTreesVisibleFromOutsideForest(const std::string_view& input, bool& success) -> HeightType;

// template<typename SizeType, SizeType Rows, SizeType Columns>
// auto GetNumTreesVisibleFromOutsideForest(const std::string_view& input, bool& success) -> std::uint64_t;

} // namespace Solutions
#endif