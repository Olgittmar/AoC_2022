#ifndef SOLUTIONS_TREETOPTREEHOUSE_FOREST_HPP
#define SOLUTIONS_TREETOPTREEHOUSE_FOREST_HPP

// Std
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
#include "Utils.hpp"

namespace Solutions::TreetopTreeHouse {

template<typename HeightType, utils::index_t Size> class Forest
{
	using TreeMap_t = std::array<std::array<HeightType, Size.column>, Size.row>;
	using VisibilityMap_t = std::array<std::array<bool, Size.column>, Size.row>;

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

	[[nodiscard]] static auto StringViewToTrees(const std::string_view& input) -> TreeMap_t;

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

	[[nodiscard]] auto
	getNumTreesVisibleFromEdge() const -> size_t
	{
	    auto countVisibleInRow = [](size_t sum, const std::array<bool, Size.column>& visibleRow)
	    {
		return std::accumulate(visibleRow.cbegin(), visibleRow.cend(), sum,
				       [](size_t subSum, bool isVisible) { return subSum + size_t(isVisible); });
	    };

	    return std::accumulate(visibleFromEdge.cbegin(), visibleFromEdge.cend(), 0, countVisibleInRow);
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

	    const auto treeRow = trees.at(index.row);
	    return treeRow.at(index.column);
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

	    const auto visibleRow = visibleFromEdge.at(index.row);
	    return visibleRow.at(index.column);
	}

    protected:
    private:

	void setTreesVisibleFromEdge();

	template<Direction Dir> void setTreesVisibleFrom(utils::index_t index);

	[[nodiscard]] auto heightAt(utils::index_t index) -> HeightType&;

	[[nodiscard]] static constexpr auto
	CharToHeightType(char character) -> HeightType
	{
	    HeightType _tmp = 0;
	    _tmp = HeightType(character) - HeightType('0');
	    return _tmp;
	}

	[[nodiscard]] static constexpr auto
	LineToHeights(const std::string_view& line) -> std::array<HeightType, Size.column>
	{
	    std::array<HeightType, Size.column> _ret{};

	    for (size_t pos = 0; pos < line.size() && pos < Size.column; ++pos)
		{
		    _ret.at(pos) = CharToHeightType(line.at(pos));
		}

	    return _ret;
	}

	TreeMap_t trees;
	VisibilityMap_t visibleFromEdge;
};

template<typename HeightType, utils::index_t Size>
auto operator<<(std::ostream& out, const Forest<HeightType, Size>& forest) -> std::ostream&;

} // namespace Solutions::TreetopTreeHouse
#endif