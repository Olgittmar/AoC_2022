#include "CampCleanup.hpp"

// Std
#include <algorithm>
#include <bits/ranges_algo.h>
#include <charconv>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace {

struct CleanupSection
{
	// uint32_t ID = 0;

	struct Range
	{
		uint32_t start = 0;
		uint32_t end = 0;
	} range;
};

struct AssignmentPair
{
	[[nodiscard]] auto
	fullyOverlaps() const -> bool
	{
	    const auto firstContainsSecond =
	      first.range.start <= second.range.start && first.range.end >= second.range.end;
	    const auto secondContainsFirst =
	      second.range.start <= first.range.start && second.range.end >= first.range.end;
	    return firstContainsSecond || secondContainsFirst;
	}

	[[nodiscard]] auto
	partiallyOverlaps() const -> bool
	{
	    // Optimize with some boolean magic
	    const auto firstContainsStartOfSecond =
	      first.range.start <= second.range.start && first.range.end >= second.range.start;
	    const auto firstContainsEndOfSecond =
	      first.range.start <= second.range.end && first.range.end >= second.range.end;
	    const auto secondContainsStartOfFirst =
	      second.range.start <= first.range.start && second.range.end >= first.range.start;
	    const auto secondContainsEndOfFirst =
	      second.range.start <= first.range.end && second.range.end >= first.range.end;
	    return firstContainsStartOfSecond || firstContainsEndOfSecond || secondContainsStartOfFirst ||
		   secondContainsEndOfFirst;
	}

	CleanupSection first;
	CleanupSection second;
};

auto
parseInput(const std::string_view& input) -> std::vector<AssignmentPair>
{
    std::vector<AssignmentPair> _ret;
    constexpr auto delimiter = '\n';
    const auto numLines = std::ranges::count(input, delimiter);
    _ret.reserve(numLines);

    auto strToCleanupSection = [](const std::string_view& data) -> CleanupSection
    {
	constexpr auto delimiter = '-';
	const auto midPos = data.find(delimiter);

	const std::string startStr{data.substr(0, midPos)};
	const uint32_t start = std::stoul(startStr);

	const std::string endStr{data.substr(midPos + 1, std::string_view::npos)};
	const uint32_t end = std::stoul(endStr);

	return CleanupSection{/*.ID = 0,*/ .range = CleanupSection::Range{.start = start, .end = end}};
    };

    auto strToAssignmentPair = [&strToCleanupSection](const std::string_view& data) -> AssignmentPair
    {
	constexpr auto delimiter = ',';
	const auto midPos = data.find(delimiter);

	const auto firstStr{data.substr(0, midPos)};
	const auto secondStr{data.substr(midPos + 1, std::string_view::npos)};

	return AssignmentPair{.first = strToCleanupSection(firstStr), .second = strToCleanupSection(secondStr)};
    };

    size_t pos = 0;

    while (pos < input.size())
	{
	    const auto nextPos = input.find(delimiter, pos);
	    const auto line = input.substr(pos, nextPos - pos);
	    pos = nextPos + size_t(nextPos != std::string_view::npos);

	    _ret.emplace_back(strToAssignmentPair(line));
	}

    return _ret;
}

} // namespace

namespace Solutions {

auto
GetNumRedundantAssignmentPairs(const std::string_view& input, bool& success) -> std::uint32_t
{
    uint32_t sum = 0;
    try
	{
	    const auto assignmentPairs = parseInput(input);
	    sum =
	      std::ranges::count_if(assignmentPairs, [](const AssignmentPair& pair) { return pair.fullyOverlaps(); });
	    success = true;
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
    } catch (...)
	{
	    std::cout << "Unhandled exception!" << std::endl;
    }

    return sum;
}

auto
GetNumPartiallyRedundantAssignmentPairs(const std::string_view& input, bool& success) -> std::uint32_t
{
    uint32_t sum = 0;
    try
	{
	    const auto assignmentPairs = parseInput(input);
	    sum = std::ranges::count_if(assignmentPairs,
					[](const AssignmentPair& pair) { return pair.partiallyOverlaps(); });
	    success = true;
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
    } catch (...)
	{
	    std::cout << "Unhandled exception!" << std::endl;
    }

    return sum;
}
} // namespace Solutions
