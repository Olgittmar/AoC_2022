#include "ElfInventory.hpp"

// Std
#include <charconv>
#include <iostream>
#include <numeric>

// Internal

namespace Solutions::ElfCalories {

ElfInventory::ElfInventory(std::string_view inventoryStr)
{
    size_t pos = 0;
    uint32_t caloriesCount = 0;
    constexpr auto lineDelim = '\n';

    while (pos < inventoryStr.size())
	{
	    const auto nextPos = inventoryStr.find(lineDelim, pos);
	    const auto caloriesStr = inventoryStr.substr(pos, nextPos - pos);

	    pos = nextPos + size_t(nextPos != std::string_view::npos);

	    const auto conversionResult = std::from_chars(caloriesStr.data(), caloriesStr.data() + caloriesStr.size(), caloriesCount);
	    if (conversionResult.ec == std::errc::invalid_argument)
		{
		    std::cout << "WARNING: unable to convert " << caloriesStr << " to caloriesCount (uint32_t)." << std::endl;
		    continue;
	    }

	    m_calories.emplace_back(caloriesCount);
	}
    m_totalCalories = std::accumulate(std::next(m_calories.cbegin()), m_calories.cend(), m_calories.front());
}

[[nodiscard]] auto
ElfInventory::getTotalCalories() const -> uint32_t
{
    return m_totalCalories;
}

void
ElfInventory::addItemCalories(uint32_t cals)
{
    m_calories.emplace_back(cals);
}

} // namespace Solutions::ElfCalories