#ifndef SOLUTIONS_TREETOPTREEHOUSE_FOREST_HPP
#define SOLUTIONS_TREETOPTREEHOUSE_FOREST_HPP

// Std
#include <string_view>
#include <vector>

// Internal
#include "Definitions.hpp"

namespace Solutions::TreetopTreeHouse {

template<typename HeightType, size_t NumRows, size_t NumColumns> class Forest
{
    public:

	static constexpr auto Width = NumColumns + 2;
	static constexpr auto Depth = NumRows + 2;

	enum class Direction
	{
	    North,
	    South,
	    East,
	    West
	};

	constexpr Forest() = default;

	Forest(const std::array<std::array<HeightType, Depth>, Width>& heights) : trees(heights) {}

	[[nodiscard]] static auto StringViewToTrees(const std::string_view& input)
	  -> std::array<std::array<HeightType, Depth>, Width>;

	[[nodiscard]] constexpr auto
	getHeightAt(size_t row, size_t column) const -> HeightType
	{
	    if (1 > column || Depth + 1 < column)
		{
		    throw std::out_of_range("column out of range");
	    }

	    if (1 > row || Width + 1 < row)
		{
		    throw std::out_of_range("row out of range");
	    }

	    const auto treeRow = trees.at(row);
	    return treeRow.at(column);
	}

	[[nodiscard]] auto getTreesVisibleFrom(size_t row, size_t column) const
	  -> std::vector<std::pair<size_t, size_t>>;

    protected:
    private:

	[[nodiscard]] auto getTreesVisibleNorthOf(size_t row, size_t col) const
	  -> std::vector<std::pair<size_t, size_t>>;
	[[nodiscard]] auto getTreesVisibleSouthOf(size_t row, size_t col) const
	  -> std::vector<std::pair<size_t, size_t>>;
	[[nodiscard]] auto getTreesVisibleEastOf(size_t row, size_t col) const
	  -> std::vector<std::pair<size_t, size_t>>;
	[[nodiscard]] auto getTreesVisibleWestOf(size_t row, size_t col) const
	  -> std::vector<std::pair<size_t, size_t>>;

	[[nodiscard]] auto heightAt(size_t row, size_t column) -> HeightType&;
	[[nodiscard]] auto getDirectionsVisibleFrom(size_t row, size_t col) const;

	[[nodiscard]] static constexpr auto
	CharToHeightType(char character) -> HeightType
	{
	    HeightType _tmp = 0;
	    _tmp = HeightType(character) - HeightType('0');
	    return _tmp;
	}

	[[nodiscard]] static constexpr auto
	LineToHeights(const std::string_view& line) -> std::array<HeightType, Width>
	{
	    std::array<HeightType, Width> _ret{};

	    for (size_t pos = 1; pos < line.size() && pos < Width - 1; ++pos)
		{
		    _ret.at(pos) = CharToHeightType(line.at(pos));
		}

	    return _ret;
	}

	std::array<std::array<HeightType, Depth>, Width> trees;
};

template<typename HeightType, size_t NumRows, size_t NumColumns>
auto operator<<(std::ostream& out, const Forest<HeightType, NumRows, NumColumns>& forest) -> std::ostream&;

} // namespace Solutions::TreetopTreeHouse
#endif