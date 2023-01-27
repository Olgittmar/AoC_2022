#include "Forest.hpp"

#include "Definitions.hpp"
#include "PrettyPrint/PrettyPrint.hpp"

// Std
#include <array>
#include <cstddef>
#include <cstdlib>
#include <experimental/source_location>
#include <iostream>
#include <unordered_set>

using source_location = std::experimental::source_location;

namespace Solutions::TreetopTreeHouse {

template<typename HeightType, utils::index_t Size>
auto
Forest<HeightType, Size>::StringViewToTrees(const std::string_view& input) -> TreeMap_t
{
    constexpr auto lineDelimiter = '\n';

    TreeMap_t initList{{}};

    size_t strPos = 0;
    for (size_t row = 0; row < Size.row && strPos < input.size(); ++row)
	{
	    const auto rowEnd = input.find(lineDelimiter, strPos);
	    const auto line = input.substr(strPos, rowEnd - strPos);

	    initList.at(row) = LineToHeights(line);
	    strPos = rowEnd + 1;
	}

    return initList;
}

template<typename HeightType, utils::index_t Size>
auto
Forest<HeightType, Size>::heightAt(utils::index_t index) -> HeightType&
{
    if (0 > index.column || Size.column < index.column)
	{
	    utils::log(std::experimental::source_location::current(), "out of range");
	    throw std::out_of_range("column out of range");
    }

    if (0 > index.row || Size.row < index.row)
	{
	    utils::log(std::experimental::source_location::current(), "out of range");
	    throw std::out_of_range("row out of range");
    }

    auto& treeRow = trees.at(index.row);
    return treeRow.at(index.column);
}

template<typename HeightType, utils::index_t Size>
void
Forest<HeightType, Size>::setTreesVisibleFromEdge()
{
    using enum Forest<HeightType, Size>::Direction;

    visibleFromEdge.fill(std::array<bool, Size.column>{false});

    // For each point on edge, walk in direction of opposite edge
    // North & South
    for (size_t col = 0; col < Size.column; ++col)
	{
	    setTreesVisibleFrom<North>(utils::index_t{Size.row - 1, col});
	    setTreesVisibleFrom<South>(utils::index_t{0, col});
	}

    for (size_t row = 0; row < Size.row; ++row)
	{
	    setTreesVisibleFrom<East>(utils::index_t{row, 0});
	    setTreesVisibleFrom<West>(utils::index_t{row, Size.column - 1});
	}
}

template<typename HeightType, utils::index_t Size>
template<typename Forest<HeightType, Size>::Direction Dir>
void
Forest<HeightType, Size>::setTreesVisibleFrom(utils::index_t index)
{
    using Direction = Forest<HeightType, Size>::Direction;
    HeightType highestSeen = 0;
    auto pos = index;

    while (!isAtEdge<Dir>(pos) && !(highestSeen >= highestTreePossible))
	{
	    const auto nextTreeHeight = getHeightAt(pos);

	    if (nextTreeHeight >= highestSeen)
		{
		    highestSeen = nextTreeHeight + 1;
		    auto& treeRow = visibleFromEdge.at(pos.row);
		    treeRow.at(pos.column) = true;
	    }

	    walk<Dir>(pos);
	}
}

template<typename HeightType, utils::index_t Size>
auto
operator<<(std::ostream& out, const Forest<HeightType, Size>& forest) -> std::ostream&
{
    // for (size_t row = 0; row < Size.row; ++row)
    // {
    //     for (size_t col = 0; col < Size.column; ++col)
    // 	{
    // 	    out << forest.getHeightAt({row, col});
    // 	}

    //     out << std::endl;
    // }

    constexpr auto greenBegin = "\x1B[320";
    constexpr auto greenEnd = "\033[0m";
    // out << std::endl;

    for (size_t row = 0; row < Size.row; ++row)
	{
	    for (size_t col = 0; col < Size.column; ++col)
		{
		    const auto pos = utils::index_t{row, col};
		    // Print with colour
		    out << (forest.isVisibleFromEdge(pos) ? greenBegin : "");
		    out << forest.getHeightAt(pos);
		    out << (forest.isVisibleFromEdge(pos) ? greenEnd : "");
		}

	    out << std::endl;
	}
    return out;
}

template class Forest<size_t, utils::index_t{NumTreeRows, NumTreeColumns}>;
template class Forest<size_t, utils::index_t{NumTreeRowsInTest, NumTreeColumnsInTest}>;

template auto operator<<(std::ostream& out, const Forest<size_t, utils::index_t{NumTreeRows, NumTreeColumns}>& forest)
  -> std::ostream&;
template auto operator<<(std::ostream& out,
			 const Forest<size_t, utils::index_t{NumTreeRowsInTest, NumTreeColumnsInTest}>& forest)
  -> std::ostream&;
} // namespace Solutions::TreetopTreeHouse