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
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace Solutions {

auto
GetCaloriesOfElfWithMostCalories(std::string_view input, bool& success) -> std::uint32_t
{
    using Inventory_t = ElfCalories::ElfInventory;
    uint32_t _ret = 0;
    const auto inventories = Inventory_t::strViewToInventory(input);
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
GetCaloriesOfTopThreeElvesWithMostCalories(std::string_view input, bool& success) -> std::uint32_t
{
    using Inventory_t = ElfCalories::ElfInventory;
    uint32_t _ret = 0;

    auto hasHigherCalorieCount = [](const Inventory_t& first, const Inventory_t& second) constexpr -> bool
    { return first.getTotalCalories() > second.getTotalCalories(); };

    auto inventories = Inventory_t::strViewToInventory(input);
    std::sort(inventories.begin(), inventories.end(), hasHigherCalorieCount);

    const auto sumOfTopThreeCaloriesCount =
      std::accumulate(std::next(inventories.begin()), std::next(inventories.begin(), 3), inventories.front().getTotalCalories(),
		      [](uint32_t Sum, const Inventory_t& inventory) { return Sum + inventory.getTotalCalories(); });

    success = true;
    _ret = sumOfTopThreeCaloriesCount;

    return _ret;
}

} // namespace Solutions
