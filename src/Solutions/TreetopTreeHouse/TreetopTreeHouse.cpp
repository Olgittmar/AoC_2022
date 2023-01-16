#include "TreetopTreeHouse.hpp"

// Std
#include <iostream>

// Internal
#include "Forest.hpp"

namespace {

} // namespace

namespace Solutions {

template<typename HeightType, size_t Rows, size_t Columns>
auto
GetNumTreesVisibleFromOutsideForest(const std::string_view& input, bool& success) -> HeightType
{
    using Forest = TreetopTreeHouse::Forest<HeightType, Rows, Columns>;

    // const auto initData = Forest<HeightType, Rows, Columns>::StringViewToHeights(input);
    const auto initData = Forest::StringViewToTrees(input);
    Forest forest{initData};

    std::cout << "Forest: " << std::endl;
    std::cout << forest;

    // Print first row
    for (size_t col = 1; col < Forest::Width - 1; ++col)
	{
	    const auto treesVisible = forest.getTreesVisibleFrom(0, col);
	}

    // Print first and last column for all rows in between first and last
    for (size_t row = 1; row < Forest::Depth - 1; ++row)
	{
	    const auto leftTreesVisible = forest.getTreesVisibleFrom(row, 0);
	    const auto rightTreesVisible = forest.getTreesVisibleFrom(row, Forest::Width);
	}

    // print last row
    for (size_t col = 1; col < Forest::Width - 1; ++col)
	{
	    const auto treesVisible = forest.getTreesVisibleFrom(Forest::Depth, col);
	}

    success = true;
    return 0;
}

// Solution template instantiations
template auto
GetNumTreesVisibleFromOutsideForest<size_t, TreetopTreeHouse::NumTreeRows, TreetopTreeHouse::NumTreeColumns>(
  const std::string_view& input, bool& success) -> size_t;

template auto GetNumTreesVisibleFromOutsideForest<size_t, TreetopTreeHouse::NumTreeRowsInTest,
						  TreetopTreeHouse::NumTreeColumnsInTest>(const std::string_view& input,
											  bool& success) -> size_t;
} // namespace Solutions