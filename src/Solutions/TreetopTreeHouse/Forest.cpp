#include "Forest.hpp"

#include "Definitions.hpp"

// Std
#include <cstddef>
#include <iostream>
#include <unordered_set>

// namespace {

// }

namespace Solutions::TreetopTreeHouse {

template<typename HeightType, size_t NumRows, size_t NumColumns>
[[nodiscard]] auto
Forest<HeightType, NumRows, NumColumns>::StringViewToTrees(const std::string_view& input)
  -> std::array<std::array<HeightType, Depth>, Width>
{
    constexpr auto lineDelimiter = '\n';

    std::array<std::array<HeightType, Depth>, Width> initList{{}};

    size_t strPos = 0;
    for (size_t row = 1; row < Depth - 1 && strPos < input.size(); ++row)
	{
	    const auto rowEnd = input.find(lineDelimiter, strPos);
	    const auto line = input.substr(strPos, rowEnd - strPos);

	    initList.at(row) = LineToHeights(line);
	    strPos = rowEnd + 1;
	}

    return initList;
}

template<typename HeightType, size_t NumRows, size_t NumColumns>
[[nodiscard]] auto
Forest<HeightType, NumRows, NumColumns>::getTreesVisibleFrom(size_t row, size_t column) const
  -> std::vector<std::pair<size_t, size_t>>
{
    std::vector<std::pair<size_t, size_t>> _ret;
    // Debug print
    auto dirToString = [](const Direction& dir) constexpr->const char*
    {
	switch (dir)
	    {
		case Direction::North:
		    return "north";
		case Direction::South:
		    return "south";
		case Direction::East:
		    return "east";
		case Direction::West:
		    return "west";
	    }
    };

    const auto visibleDirections = getDirectionsVisibleFrom(row, column);
    std::cout << "row: " << row << " col: " << column << std::endl;

    for (Direction dir : visibleDirections)
	{
	    std::cout << "I can see " << dirToString(dir) << std::endl;
	    std::vector<std::pair<size_t, size_t>> _tmp;

	    switch (dir)
		{
		    case Direction::North:
			{
			    _tmp = getTreesVisibleNorthOf(row, column);
			    break;
			}
		    case Direction::South:
			{
			    _tmp = getTreesVisibleSouthOf(row, column);
			    break;
			}
		    case Direction::East:
			{
			    _tmp = getTreesVisibleEastOf(row, column);
			    break;
			}
		    case Direction::West:
			{
			    _tmp = getTreesVisibleWestOf(row, column);
			    break;
			}
		}

	    _ret.insert(_ret.end(), _tmp.cbegin(), _tmp.cend());
	}

    return {};
}

template<typename HeightType, size_t NumRows, size_t NumColumns>
[[nodiscard]] auto
Forest<HeightType, NumRows, NumColumns>::heightAt(size_t row, size_t column) -> HeightType&
{
    if (1 > column || Depth + 1 < column)
	{
	    throw std::out_of_range("column out of range");
    }

    if (1 > row || Width + 1 < row)
	{
	    throw std::out_of_range("row out of range");
    }

    auto& treeRow = trees.at(row);
    return treeRow.at(column);
}

template<typename HeightType, size_t NumRows, size_t NumColumns>
[[nodiscard]] auto
Forest<HeightType, NumRows, NumColumns>::getDirectionsVisibleFrom(size_t row, size_t col) const
{
    std::unordered_set<Direction> visibleDirections;
    if (!(1 > row) && (col > 0 && col < Width))
	{
	    visibleDirections.emplace(Direction::North);
    }

    if (!(Depth - 1 < row) && (col > 0 && col < Width))
	{
	    visibleDirections.emplace(Direction::South);
    }

    if (!(Width - 1 < col) && (row > 0 && row < Depth))
	{
	    visibleDirections.emplace(Direction::East);
    }

    if (!(1 > col) && (row > 0 && row < Depth))
	{
	    visibleDirections.emplace(Direction::West);
    }

    return visibleDirections;
}

template<typename HeightType, size_t NumRows, size_t NumColumns>
[[nodiscard]] auto
Forest<HeightType, NumRows, NumColumns>::getTreesVisibleNorthOf(size_t row, size_t col) const
  -> std::vector<std::pair<size_t, size_t>>
{
    return {};
}

template<typename HeightType, size_t NumRows, size_t NumColumns>
[[nodiscard]] auto
Forest<HeightType, NumRows, NumColumns>::getTreesVisibleSouthOf(size_t row, size_t col) const
  -> std::vector<std::pair<size_t, size_t>>
{
    return {};
}

template<typename HeightType, size_t NumRows, size_t NumColumns>
[[nodiscard]] auto
Forest<HeightType, NumRows, NumColumns>::getTreesVisibleEastOf(size_t row, size_t col) const
  -> std::vector<std::pair<size_t, size_t>>
{
    return {};
}

template<typename HeightType, size_t NumRows, size_t NumColumns>
[[nodiscard]] auto
Forest<HeightType, NumRows, NumColumns>::getTreesVisibleWestOf(size_t row, size_t col) const
  -> std::vector<std::pair<size_t, size_t>>
{
    return {};
}

template<typename HeightType, size_t NumRows, size_t NumColumns>
auto
operator<<(std::ostream& out, const Forest<HeightType, NumRows, NumColumns>& forest) -> std::ostream&
{
    constexpr auto Width = NumColumns + 2;
    constexpr auto Depth = NumRows + 2;

    for (size_t row = 1; row < Depth - 1; ++row)
	{
	    for (size_t col = 1; col < Width - 1; ++col)
		{
		    out << forest.getHeightAt(row, col);
		}

	    out << std::endl;
	}
    return out;
}

template class Forest<size_t, NumTreeRows, NumTreeColumns>;
template class Forest<size_t, NumTreeRowsInTest, NumTreeColumnsInTest>;

template auto operator<<(std::ostream& out, const Forest<size_t, NumTreeRows, NumTreeColumns>& forest) -> std::ostream&;
template auto operator<<(std::ostream& out, const Forest<size_t, NumTreeRowsInTest, NumTreeColumnsInTest>& forest)
  -> std::ostream&;
} // namespace Solutions::TreetopTreeHouse