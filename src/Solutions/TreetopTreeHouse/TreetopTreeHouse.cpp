#include "TreetopTreeHouse.hpp"

// Std
#include <iostream>

// Internal
#include "Definitions.hpp"
#include "Forest.hpp"
#include "PrettyPrint/PrettyPrint.hpp"

namespace Solutions {

template<typename HeightType, utils::index_t Size>
auto
GetNumTreesVisibleFromOutsideForest(const std::string_view& input, bool& success) -> HeightType
{
    using Forest = TreetopTreeHouse::Forest<HeightType, Size>;

    // const auto initData = Forest<HeightType, Rows, Columns>::StringViewToHeights(input);
    const auto initData = Forest::StringViewToTrees(input);
    Forest forest{initData};
    forest.updateVisibility();

    utils::log(std::experimental::source_location::current(), "Forest: \n", forest);
    const auto numTreesVisibleFromEdge = forest.getNumTreesVisibleFromEdge();

    success = true;
    return numTreesVisibleFromEdge;
}

// Solution template instantiations
template auto GetNumTreesVisibleFromOutsideForest<size_t, utils::index_t{TreetopTreeHouse::NumTreeRows,
									 TreetopTreeHouse::NumTreeColumns}>(
  const std::string_view& input, bool& success) -> size_t;

template auto GetNumTreesVisibleFromOutsideForest<size_t, utils::index_t{TreetopTreeHouse::NumTreeRowsInTest,
									 TreetopTreeHouse::NumTreeColumnsInTest}>(
  const std::string_view& input, bool& success) -> size_t;
} // namespace Solutions