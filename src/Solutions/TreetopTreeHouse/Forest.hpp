#ifndef SOLUTIONS_TREETOPTREEHOUSE_FOREST_HPP
#define SOLUTIONS_TREETOPTREEHOUSE_FOREST_HPP

// Std
#include <algorithm>
#include <array>
#include <cstddef>
#include <experimental/source_location>
#include <numeric>
#include <string_view>
#include <unordered_set>
#include <vector>

// Internal
#include "Coordinates/Coordinates2D.hpp"
#include "Definitions.hpp"
#include "PrettyPrint/PrettyPrint.hpp"
#include "Utils.hpp"

namespace Solutions::TreetopTreeHouse {

template<typename HeightType, utils::index_t Size> class Forest
{
	using TreeMap_t = std::array<HeightType, size_t(Size.row* Size.column)>;
	using VisibilityMap_t = std::array<bool, size_t(Size.row* Size.column)>;

	enum class Direction
	{
	    North,
	    South,
	    East,
	    West
	};

	template<Direction Dir>
	static constexpr void
	walk(utils::index_t& pos)
	{
	    using enum Direction;
	    switch (Dir)
		{
		    case North:
			{
			    pos.row -= 1;
			    return;
			}
		    case South:
			{
			    pos.row += 1;
			    return;
			}
		    case East:
			{
			    pos.column += 1;
			    return;
			}
		    case West:
			{
			    pos.column -= 1;
			    return;
			}
		}
	};

	template<Direction Dir> [[nodiscard]] auto isAtEdge(utils::index_t pos) const -> bool;

	template<>
	[[nodiscard]] auto
	isAtEdge<Direction::North>(utils::index_t pos) const -> bool
	{
	    return !(0 < pos.row);
	};

	template<>
	[[nodiscard]] auto
	isAtEdge<Direction::South>(utils::index_t pos) const -> bool
	{
	    return !(Size.row > pos.row);
	};

	template<>
	[[nodiscard]] auto
	isAtEdge<Direction::East>(utils::index_t pos) const -> bool
	{
	    return !(Size.column > pos.column);
	};

	template<>
	[[nodiscard]] auto
	isAtEdge<Direction::West>(utils::index_t pos) const -> bool
	{
	    return !(0 < pos.column);
	};

    public:

	constexpr Forest() = default;
	constexpr Forest(const TreeMap_t& heights) : trees(heights) {}

	[[nodiscard]] static auto StringViewToTrees(std::string_view input) -> TreeMap_t;

	[[nodiscard]] auto
	getTreesVisibleFromEdge() const -> VisibilityMap_t
	{
	    return visibleFromEdge;
	}

	inline void
	updateVisibility()
	{
	    setTreesVisibleFromEdge();
	}

	inline void
	updateVisibilityScore()
	{
	    calculateVisibilityScores();
	}

	[[nodiscard]] auto getVisibleDistanceScoreMap() const -> TreeMap_t;

	[[nodiscard]] auto
	getHighestVisibilityScore() const -> HeightType
	{
	    const auto visibilityScores = getVisibleDistanceScoreMap();
	    return std::ranges::max(visibilityScores);
	}

	[[nodiscard]] constexpr auto
	getVisibleDistances() const
	{
	    return std::array<TreeMap_t, 4>{
	      visibleDistanceNorth,
	      visibleDistanceSouth,
	      visibleDistanceEast,
	      visibleDistanceWest,
	    };
	}

	[[nodiscard]] auto
	getNumTreesVisibleFromEdge() const -> size_t
	{
	    return std::accumulate(visibleFromEdge.cbegin(), visibleFromEdge.cend(), 0,
				   [](size_t subSum, bool isVisible) { return subSum + size_t(isVisible); });
	}

	[[nodiscard]] constexpr auto
	getHeightAt(utils::index_t index) const -> HeightType
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

	    return trees.at(index.row * Size.column + index.column);
	}

	[[nodiscard]] constexpr auto
	isVisibleFromEdge(utils::index_t index) const -> bool
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

	    return visibleFromEdge.at(index.row * Size.column + index.column);
	}

    protected:
    private:

	void setTreesVisibleFromEdge();
	void calculateVisibilityScores();

	template<Direction Dir> void setTreesVisibleFrom(utils::index_t index);

	template<Direction Dir> void setVisibleDistance(utils::index_t index);

	[[nodiscard]] auto
	heightAt(utils::index_t index) -> HeightType&
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

	    return trees.at(index.row * Size.column + index.column);
	}

	[[nodiscard]] static constexpr auto
	CharToHeightType(char character) -> HeightType
	{
	    HeightType _tmp = 0;
	    _tmp = HeightType(character) - HeightType('0');
	    return _tmp;
	}

	TreeMap_t trees;
	VisibilityMap_t visibleFromEdge;

	TreeMap_t visibleDistanceNorth;
	TreeMap_t visibleDistanceSouth;
	TreeMap_t visibleDistanceEast;
	TreeMap_t visibleDistanceWest;
};

template<typename HeightType, utils::index_t Size> auto operator<<(std::ostream& out, const Forest<HeightType, Size>& forest) -> std::ostream&;

} // namespace Solutions::TreetopTreeHouse
#endif