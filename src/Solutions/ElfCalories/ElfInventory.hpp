#ifndef SOLUTIONS_ELFCALORIES_ELFINVENTORY_HPP
#define SOLUTIONS_ELFCALORIES_ELFINVENTORY_HPP

// std
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <vector>

// internal

namespace Solutions::ElfCalories {

class ElfInventory
{
    public:

	explicit ElfInventory(std::string_view inventoryStr);

	[[nodiscard]] inline auto
	getTotalCalories() const -> uint32_t
	{
	    return m_totalCalories;
	}

	static auto strViewToInventory(std::string_view input) -> std::vector<ElfInventory>;

    private:

	uint32_t m_totalCalories;
};

} // namespace Solutions::ElfCalories
#endif