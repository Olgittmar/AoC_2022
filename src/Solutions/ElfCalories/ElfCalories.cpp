#include "ElfCalories.hpp"

// Own
#include <Utils.hpp>

// Internal
#include "ElfInventory.hpp"

// std
#include <algorithm>
#include <charconv>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

namespace {
auto
parseInput(const std::string_view& input) -> std::vector<Solutions::ElfCalories::ElfInventory>
{
    std::vector<Solutions::ElfCalories::ElfInventory> _ret;
    size_t pos = 0;
    const std::string delimiter = "\n\n";

    while (pos < input.size())
	{
	    const auto nextPos = input.find(delimiter, pos);
	    const auto inventoryStr = input.substr(pos, nextPos - pos);
	    pos = nextPos + size_t(nextPos != std::string_view::npos) * delimiter.size();

	    if (inventoryStr.empty())
		{
		    continue;
	    }

	    _ret.emplace_back(inventoryStr);
	}

    return _ret;
}

} // namespace

namespace Solutions {

auto
GetCaloriesOfElfWithMostCalories(const std::string_view& input, bool& success) -> std::uint32_t
{
    uint32_t _ret = 0;
    const auto inventories = parseInput(input);
    uint32_t highestCaloriesCount = 0;

    for (const auto& inventory : inventories)
	{
	    const auto totCals = inventory.getTotalCalories();
	    highestCaloriesCount = (totCals > highestCaloriesCount ? totCals : highestCaloriesCount);
	}

    success = true;
    _ret = highestCaloriesCount;

    return _ret;
}

auto
GetCaloriesOfTopThreeElvesWithMostCalories(const std::string_view& input, bool& success) -> std::uint32_t
{
    uint32_t _ret = 0;

    auto hasHigherCalorieCount = [](const Solutions::ElfCalories::ElfInventory& first,
				    const Solutions::ElfCalories::ElfInventory& second) -> bool
    { return first.getTotalCalories() > second.getTotalCalories(); };

    auto inventories = parseInput(input);
    std::sort(inventories.begin(), inventories.end(), hasHigherCalorieCount);

    const auto sumOfTopThreeCaloriesCount = std::accumulate(
      std::next(inventories.begin()), std::next(inventories.begin(), 3), inventories.front().getTotalCalories(),
      [](uint32_t Sum, const Solutions::ElfCalories::ElfInventory& inventory)
      { return Sum + inventory.getTotalCalories(); });

    success = true;
    _ret = sumOfTopThreeCaloriesCount;

    return _ret;
}

} // namespace Solutions
