#include "Forest.hpp"

#include "Definitions.hpp"
#include "PrettyPrint/PrettyPrint.hpp"

// Std
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <experimental/source_location>
#include <iostream>
#include <memory>
#include <stdexcept>
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

	    for (size_t pos = 0; pos < line.size() && pos < Size.column; ++pos)
		{
		    initList.at(row * Size.column + pos) = CharToHeightType(line.at(pos));
		}

	    strPos = rowEnd + 1;
	}

    return initList;
}

template<typename HeightType, utils::index_t Size>
void
Forest<HeightType, Size>::setTreesVisibleFromEdge()
{
    using enum Forest<HeightType, Size>::Direction;

    visibleFromEdge.fill(false);

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
void
Forest<HeightType, Size>::calculateVisibilityScores()
{
    using enum Forest<HeightType, Size>::Direction;

    visibleDistanceNorth.fill(0);
    visibleDistanceSouth.fill(0);
    visibleDistanceEast.fill(0);
    visibleDistanceWest.fill(0);

    for (size_t col = 0; col < Size.column; ++col)
	{
	    setVisibleDistance<North>(utils::index_t{Size.row - 1, col});
	    setVisibleDistance<South>(utils::index_t{0, col});
	}

    for (size_t row = 0; row < Size.row; ++row)
	{
	    setVisibleDistance<East>(utils::index_t{row, 0});
	    setVisibleDistance<West>(utils::index_t{row, Size.column - 1});
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

    while (!isAtEdge<Dir>(pos) && !(highestSeen > highestTreePossible))
	{
	    const auto nextTreeHeight = getHeightAt(pos);

	    if (nextTreeHeight >= highestSeen)
		{
		    highestSeen = nextTreeHeight + 1;
		    visibleFromEdge.at(pos.row * Size.column + pos.column) = true;
	    }

	    walk<Dir>(pos);
	}
}

template<typename HeightType, utils::index_t Size>
template<typename Forest<HeightType, Size>::Direction Dir>
void
Forest<HeightType, Size>::setVisibleDistance(utils::index_t index)
{
    using Direction = Forest<HeightType, Size>::Direction;

    auto& visibleDistanceInDir = [this]() constexpr->TreeMap_t&
    {
	switch (Dir)
	    {
		case Direction::North:
		    return visibleDistanceNorth;
		case Direction::South:
		    return visibleDistanceSouth;
		case Direction::East:
		    return visibleDistanceEast;
		case Direction::West:
		    return visibleDistanceWest;
	    }
    }
    ();

    std::array<size_t, highestTreePossible + 1> distSinceLastSeen{0};

    while (!isAtEdge<Dir>(index))
	{
	    const auto treeHeight = getHeightAt(index);

	    // TODO: What is going on here?
	    const auto* const distToLastBlockingTree =
	      std::ranges::min_element(std::next(distSinceLastSeen.cbegin(), treeHeight), distSinceLastSeen.cend());

	    visibleDistanceInDir.at(index.row * Size.column + index.column) = *distToLastBlockingTree;

	    distSinceLastSeen.at(treeHeight) = 0;

	    walk<Dir>(index);
	    for (auto& dist : distSinceLastSeen)
		{
		    dist += 1;
		}
	}
}

template<typename HeightType, utils::index_t Size>
auto
Forest<HeightType, Size>::getVisibleDistanceScoreMap() const -> TreeMap_t
{
    TreeMap_t _ret;
    for (size_t idx = 0UL; idx < Size.row * Size.column; ++idx)
	{
	    _ret.at(idx) = (visibleDistanceNorth.at(idx) * visibleDistanceSouth.at(idx) * visibleDistanceEast.at(idx) *
			    visibleDistanceWest.at(idx));
	}
    return _ret;
}

template<typename HeightType, utils::index_t Size>
auto
operator<<(std::ostream& out, const Forest<HeightType, Size>& forest) -> std::ostream&
{
    using utils::Color::Foreground::GREEN;
    using utils::Color::Foreground::RED;

    using utils::Color::RESET;

    // Print the forest itself
    for (size_t row = 0; row < Size.row; ++row)
	{
	    for (size_t col = 0; col < Size.column; ++col)
		{
		    const auto pos = utils::index_t{row, col};
		    if (forest.isVisibleFromEdge(pos))
			{
			    // Print with colour
			    out << GREEN << forest.getHeightAt(pos) << RESET;
		    } else
			{
			    out << RED << forest.getHeightAt(pos) << RESET;
			}
		}

	    out << std::endl;
	}

    for (const auto& distMap : forest.getVisibleDistances())
	{
	    out << '\n';
	    for (size_t row = 0; row < Size.row; ++row)
		{
		    for (size_t col = 0; col < Size.column; ++col)
			{
			    out << distMap.at(row * Size.column + col);
			}

		    out << std::endl;
		}
	}

    const auto distScoreMap = forest.getVisibleDistanceScoreMap();
    out << '\n';
    for (size_t row = 0; row < Size.row; ++row)
	{
	    for (size_t col = 0; col < Size.column; ++col)
		{
		    out << distScoreMap.at(row * Size.column + col);
		}

	    out << std::endl;
	}
    // Print the distance since last seen in each direction
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