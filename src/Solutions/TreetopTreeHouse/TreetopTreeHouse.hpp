#ifndef SOLUTIONS_TREETOPTREEHOUSE_TREETOPTREEHOUSE_HPP
#define SOLUTIONS_TREETOPTREEHOUSE_TREETOPTREEHOUSE_HPP

#include "Utils.hpp"

#include <cstddef>
#include <string_view>

namespace Solutions {
template<typename HeightType, utils::index_t Size>
auto GetNumTreesVisibleFromOutsideForest(const std::string_view& input, bool& success) -> HeightType;

// template<typename SizeType, SizeType Rows, SizeType Columns>
// auto GetNumTreesVisibleFromOutsideForest(const std::string_view& input, bool& success) -> std::uint64_t;

} // namespace Solutions
#endif