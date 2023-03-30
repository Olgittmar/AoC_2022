#ifndef SOLUTIONS_ELFCALORIES_ELFINVENTORY_HPP
#define SOLUTIONS_ELFCALORIES_ELFINVENTORY_HPP

// std
#include <vector>

// internal

namespace Solutions::ElfCalories {

class ElfInventory
{
    public:

	explicit ElfInventory(std::string_view inventoryStr);

	ElfInventory(const ElfInventory& other) = default;
	ElfInventory(ElfInventory&& other) = default;
	auto operator=(const ElfInventory& other) -> ElfInventory& = default;
	auto operator=(ElfInventory&& other) -> ElfInventory& = default;
	~ElfInventory() = default;

	[[nodiscard]] auto getTotalCalories() const -> uint32_t;
	void addItemCalories(uint32_t cals);

    private:

	std::vector<uint32_t> m_calories = {};
	uint32_t m_totalCalories = 0;
};

} // namespace Solutions::ElfCalories
#endif