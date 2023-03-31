#include "ElfInventory.hpp"

#include "PrettyPrint/PrettyPrint.hpp"

// Std
#include <algorithm>
#include <charconv>
#include <iostream>
#include <numeric>
#include <ranges>
#include <source_location>
#include <string>
#include <string_view>
#include <vector>

// Internal

namespace Solutions::ElfCalories {

ElfInventory::ElfInventory(std::string_view inventoryStr)
{
    constexpr std::string_view lineDelim{"\n"};

    const auto lines = std::views::split(inventoryStr, lineDelim);

    auto subRangeToCaloryCount = [](auto&& subRange) -> uint32_t
    {
	const uint32_t caloriesCount = std::stoul(std::string(&*(subRange.begin()), std::ranges::distance(subRange)));
	return caloriesCount;
    };

    m_totalCalories = std::transform_reduce(lines.begin(), lines.end(), 0U, std::plus{}, subRangeToCaloryCount);
}

auto
ElfInventory::strViewToInventory(std::string_view input) -> std::vector<ElfInventory>
{
    constexpr std::string_view delimiter{"\n\n"};
    std::vector<ElfInventory> _ret;

    const auto inventoryBlocks = std::views::split(input, delimiter);

    auto inventoryBlockToInventory = [&_ret](auto&& subRange) constexpr
    {
	const std::string_view tmp(&*(subRange.begin()), std::ranges::distance(subRange));
	_ret.emplace_back(tmp);
    };

    std::ranges::for_each(inventoryBlocks, inventoryBlockToInventory);

    return _ret;
}

} // namespace Solutions::ElfCalories