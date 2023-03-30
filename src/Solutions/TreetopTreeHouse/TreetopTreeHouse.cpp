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
GetNumTreesVisibleFromOutsideForest(std::string_view input, bool& success) -> HeightType
{
    using Forest = TreetopTreeHouse::Forest<HeightType, Size>;

    const auto initData = Forest::StringViewToTrees(input);
    Forest forest{initData};
    forest.updateVisibility();

    const auto numTreesVisibleFromEdge = forest.getNumTreesVisibleFromEdge();

    success = true;
    return numTreesVisibleFromEdge;
}

template<typename HeightType, utils::index_t Size>
auto
GetVisibilityScoreOfHighestScoringTree(std::string_view input, bool& success) -> HeightType
{
    using Forest = TreetopTreeHouse::Forest<HeightType, Size>;

    const auto initData = Forest::StringViewToTrees(input);
    Forest forest{initData};
    forest.updateVisibilityScore();

    auto _ret = forest.getHighestVisibilityScore();

    success = true;
    return _ret;
}

// Solution template instantiations
template auto
GetNumTreesVisibleFromOutsideForest<size_t, utils::index_t{TreetopTreeHouse::NumTreeRows, TreetopTreeHouse::NumTreeColumns}>(std::string_view input,
															     bool& success) -> size_t;

template auto GetNumTreesVisibleFromOutsideForest<size_t, utils::index_t{TreetopTreeHouse::NumTreeRowsInTest, TreetopTreeHouse::NumTreeColumnsInTest}>(
  std::string_view input, bool& success) -> size_t;

template auto
GetVisibilityScoreOfHighestScoringTree<size_t, utils::index_t{TreetopTreeHouse::NumTreeRows, TreetopTreeHouse::NumTreeColumns}>(std::string_view input,
																bool& success) -> size_t;

template auto GetVisibilityScoreOfHighestScoringTree<size_t, utils::index_t{TreetopTreeHouse::NumTreeRowsInTest, TreetopTreeHouse::NumTreeColumnsInTest}>(
  std::string_view input, bool& success) -> size_t;
} // namespace Solutions