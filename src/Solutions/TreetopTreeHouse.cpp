#include "TreetopTreeHouse.hpp"

#include <array>
#include <bits/ranges_algo.h>
#include <charconv>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace {

template<typename HeightType, size_t NumRows, size_t NumColumns> class Forest
{
    public:

	constexpr Forest() = default;

	Forest(const std::array<std::array<HeightType, NumRows>, NumColumns>& heights) : trees(heights) {}

	Forest(const std::array<HeightType, NumRows * NumColumns>& heights)
	{
	    for (size_t row = 0; row < NumRows; ++row)
		{
		    auto& treeRow = trees.at(row);
		    for (size_t col = 0; col < NumColumns; ++col)
			{
			    const auto pos = row * NumRows + col;
			    heightAt(row, col) = heights.at(pos);
			}
		}
	}

	[[nodiscard]] static auto
	StringViewToHeights(const std::string_view& input) -> std::array<HeightType, NumRows * NumColumns>
	{
	    constexpr auto lineDelimiter = '\n';

	    std::array<HeightType, NumRows * NumColumns> initList{};
	    size_t strPos = 0;

	    for (size_t row = 0; row < NumRows && strPos < input.size(); ++row)
		{
		    const auto rowEnd = input.find(lineDelimiter, strPos);
		    const auto line = input.substr(strPos, rowEnd - strPos);

		    const auto heightsInLine = LineToHeights(line);

		    strPos = rowEnd + 1;

		    for (size_t col = 0; col < NumColumns; ++col)
			{
			    initList.at(row * NumColumns + col) = heightsInLine.at(col);
			}
		}

	    return initList;
	}

	[[nodiscard]] static auto
	StringViewToTrees(const std::string_view& input) -> std::array<std::array<HeightType, NumRows>, NumColumns>
	{
	    constexpr auto lineDelimiter = '\n';

	    std::array<std::array<HeightType, NumRows>, NumColumns> initList{{}};

	    size_t strPos = 0;
	    for (size_t row = 0; row < NumRows && strPos < input.size(); ++row)
		{
		    const auto rowEnd = input.find(lineDelimiter, strPos);
		    const auto line = input.substr(strPos, rowEnd - strPos);

		    initList.at(row) = LineToHeights(line);
		    strPos = rowEnd + 1;
		}

	    return initList;
	}

	[[nodiscard]] constexpr auto
	getHeightAt(size_t row, size_t column) const -> HeightType
	{
	    const auto treeRow = trees.at(row);
	    return treeRow.at(column);
	}

	[[nodiscard]] auto
	getTreesVisibleFrom(size_t row, size_t column) const -> std::vector<std::pair<size_t, size_t>>
	{
	    const auto visibleDirections = getDirectionsVisibleFrom(row, column);
	    std::cout << "row: " << row << " col: " << column << std::endl;
	    std::cout << "can see north: " << (visibleDirections.north ? "true" : "false") << std::endl;
	    std::cout << "can see south: " << (visibleDirections.south ? "true" : "false") << std::endl;
	    std::cout << "can see east: " << (visibleDirections.east ? "true" : "false") << std::endl;
	    std::cout << "can see west: " << (visibleDirections.west ? "true" : "false") << std::endl;

	    return {};
	}

    protected:
    private:

	// TODO: Consider making the outline represent the number of trees visible from that spot.
	// static constexpr auto Width = NumColumns + 2;
	// static constexpr auto Depth = NumRows + 2;

	[[nodiscard]] auto
	heightAt(size_t row, size_t column) -> HeightType&
	{
	    auto& treeRow = trees.at(row);
	    return treeRow.at(column);
	}

	[[nodiscard]] auto
	getDirectionsVisibleFrom(size_t row, size_t column) const
	{
	    struct
	    {
		    bool north;
		    bool south;
		    bool east;
		    bool west;
	    } visibleDirections{// br
				.north = !(0 >= row),
				.south = !(NumRows <= row),
				.east = !(NumColumns <= column),
				.west = !(0 >= column)};

	    return visibleDirections;
	}

	[[nodiscard]] static auto
	CharToHeightType(char character) -> HeightType
	{
	    HeightType _tmp = 0;
	    _tmp = HeightType(character) - HeightType('0');
	    // std::cout << character << " converted to " << _tmp << std::endl;
	    return _tmp;
	}

	[[nodiscard]] static auto
	LineToHeights(const std::string_view& line) -> std::array<HeightType, NumColumns>
	{
	    std::array<HeightType, NumColumns> _ret{};

	    for (size_t pos = 0; pos < line.size() && pos < NumColumns; ++pos)
		{
		    _ret.at(pos) = CharToHeightType(line.at(pos));
		}

	    return _ret;
	}

	std::array<std::array<HeightType, NumRows>, NumColumns> trees;
};

template<typename HeightType, size_t NumRows, size_t NumColumns>
auto
operator<<(std::ostream& out, const Forest<HeightType, NumRows, NumColumns>& forest) -> std::ostream&
{
    for (size_t row = 0; row < NumRows; ++row)
	{
	    for (size_t col = 0; col < NumColumns; ++col)
		{
		    out << forest.getHeightAt(row, col);
		}

	    out << std::endl;
	}
    return out;
}

} // namespace

namespace Solutions {

template<typename HeightType, size_t Rows, size_t Columns>
auto
GetNumTreesVisibleFromOutsideForest(const std::string_view& input, bool& success) -> HeightType
{
    // const auto initData = Forest<HeightType, Rows, Columns>::StringViewToHeights(input);
    const auto initData = Forest<HeightType, Rows, Columns>::StringViewToTrees(input);
    Forest<HeightType, Rows, Columns> forest{initData};

    std::cout << "Forest: " << std::endl;
    std::cout << forest;

    for (size_t row = 0; row < Rows; ++row)
	{
	    if (0 == row || Rows == row + 1)
		{
		    for (size_t col = 0; col < Columns; ++col)
			{
			    const auto treesVisible = forest.getTreesVisibleFrom(row, col);
			}
	    } else
		{
		    const auto leftTreesVisible = forest.getTreesVisibleFrom(row, 0);
		    const auto rightTreesVisible = forest.getTreesVisibleFrom(row, Columns - 1);
		}
	}
    success = true;
    return 0;
}

// Solution template instantiations
template auto GetNumTreesVisibleFromOutsideForest<size_t, NumTreeRows, NumTreeColumns>(const std::string_view& input,
										       bool& success) -> size_t;

template auto
GetNumTreesVisibleFromOutsideForest<size_t, NumTreeRowsInTest, NumTreeColumnsInTest>(const std::string_view& input,
										     bool& success) -> size_t;
} // namespace Solutions