#include "AssignmentPair.hpp"

// Std
#include <algorithm>
#include <ranges>

namespace {
using CleanupSection = Solutions::CampCleanup::CleanupSection;
using AssignmentPair = Solutions::CampCleanup::AssignmentPair;

[[nodiscard]] auto
stringToCleanupSection(const std::string_view& data) -> CleanupSection
{
    constexpr auto delimiter = '-';
    const auto midPos = data.find(delimiter);

    const std::string startStr{data.substr(0, midPos)};
    const uint32_t start = std::stoul(startStr);

    const std::string endStr{data.substr(midPos + 1, std::string_view::npos)};
    const uint32_t end = std::stoul(endStr);

    return CleanupSection{.range = CleanupSection::Range{.start = start, .end = end}};
}

[[nodiscard]] auto
stringToAssignmentPair(const std::string_view& data) -> AssignmentPair
{
    constexpr auto delimiter = ',';
    const auto midPos = data.find(delimiter);

    const auto firstStr{data.substr(0, midPos)};
    const auto secondStr{data.substr(midPos + 1, std::string_view::npos)};

    return AssignmentPair{.first = stringToCleanupSection(firstStr), .second = stringToCleanupSection(secondStr)};
}

} // namespace

namespace Solutions::CampCleanup {

[[nodiscard]] auto
AssignmentPair::fullyOverlaps() const -> bool
{
    const auto firstContainsSecond = first.range.start <= second.range.start && first.range.end >= second.range.end;
    const auto secondContainsFirst = second.range.start <= first.range.start && second.range.end >= first.range.end;
    return firstContainsSecond || secondContainsFirst;
}

[[nodiscard]] auto
AssignmentPair::partiallyOverlaps() const -> bool
{
    // Optimize with some boolean magic
    const auto firstContainsStartOfSecond =
      first.range.start <= second.range.start && first.range.end >= second.range.start;
    const auto firstContainsEndOfSecond = first.range.start <= second.range.end && first.range.end >= second.range.end;
    const auto secondContainsStartOfFirst =
      second.range.start <= first.range.start && second.range.end >= first.range.start;
    const auto secondContainsEndOfFirst = second.range.start <= first.range.end && second.range.end >= first.range.end;
    return firstContainsStartOfSecond || firstContainsEndOfSecond || secondContainsStartOfFirst ||
	   secondContainsEndOfFirst;
}

auto
stringToAssignmentPairs(const std::string_view& input) -> std::vector<AssignmentPair>
{
    std::vector<AssignmentPair> _ret;
    constexpr auto delimiter = '\n';
    const auto numLines = std::ranges::count(input, delimiter);
    _ret.reserve(numLines);

    size_t pos = 0;

    while (pos < input.size())
	{
	    const auto nextPos = input.find(delimiter, pos);
	    const auto line = input.substr(pos, nextPos - pos);
	    pos = nextPos + size_t(nextPos != std::string_view::npos);

	    _ret.emplace_back(stringToAssignmentPair(line));
	}

    return _ret;
}

} // namespace Solutions::CampCleanup