#include "ElfCalories.hpp"
// Own
#include <Utils.hpp>

// std
#include <algorithm>
#include <charconv>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

namespace {
class ElfInventory
{
    public:

	explicit ElfInventory(const std::string_view& inventoryStr)
	{
	    size_t pos = 0;
	    uint32_t caloriesCount = 0;

	    while (pos < inventoryStr.size())
		{
		    const auto nextPos = inventoryStr.find('\n', pos);
		    const auto caloriesStr = inventoryStr.substr(pos, nextPos - pos);

		    pos = nextPos + size_t(nextPos != std::string_view::npos);

		    const auto conversionResult =
		      std::from_chars(caloriesStr.data(), caloriesStr.data() + caloriesStr.size(), caloriesCount);
		    if (conversionResult.ec == std::errc::invalid_argument)
			{
			    std::cout << "WARNING: unable to convert " << caloriesStr << " to caloriesCount (uint32_t)."
				      << std::endl;
			    continue;
		    }

		    m_calories.emplace_back(caloriesCount);
		}
	    m_totalCalories = std::accumulate(std::next(m_calories.cbegin()), m_calories.cend(), m_calories.front());
	}

	ElfInventory(const ElfInventory& other) = default;
	ElfInventory(ElfInventory&& other) = default;
	auto operator=(const ElfInventory& other) -> ElfInventory& = default;
	auto operator=(ElfInventory&& other) -> ElfInventory& = default;
	~ElfInventory() = default;

	[[nodiscard]] auto
	getTotalCalories() const -> uint32_t
	{
	    return m_totalCalories;
	}

	void
	addItemCalories(uint32_t cals)
	{
	    m_calories.emplace_back(cals);
	}

    private:

	std::vector<uint32_t> m_calories = {};
	uint32_t m_totalCalories = 0;
};

auto
parseInput(const std::string_view& input) -> std::vector<ElfInventory>
{
    std::vector<ElfInventory> _ret;
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
    try
	{
	    const auto inventories = parseInput(input);
	    uint32_t highestCaloriesCount = 0;

	    for (const auto& inventory : inventories)
		{
		    const auto totCals = inventory.getTotalCalories();
		    highestCaloriesCount = (totCals > highestCaloriesCount ? totCals : highestCaloriesCount);
		}

	    success = true;
	    return highestCaloriesCount;
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
    }

    return 0;
}

auto
GetCaloriesOfTopThreeElvesWithMostCalories(const std::string_view& input, bool& success) -> std::uint32_t
{
    auto hasHigherCalorieCount = [](const ElfInventory& first, const ElfInventory& second) -> bool
    { return first.getTotalCalories() > second.getTotalCalories(); };

    try
	{
	    auto inventories = parseInput(input);
	    std::sort(inventories.begin(), inventories.end(), hasHigherCalorieCount);

	    const auto sumOfTopThreeCaloriesCount = std::accumulate(
	      std::next(inventories.begin()), std::next(inventories.begin(), 3), inventories.front().getTotalCalories(),
	      [](uint32_t Sum, const ElfInventory& inventory) { return Sum + inventory.getTotalCalories(); });

	    success = true;
	    return sumOfTopThreeCaloriesCount;
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
    }

    return 0;
}
} // namespace Solutions
