#ifndef SOLUTIONS_RUCKSACK_RUCKSACK_HPP
#define SOLUTIONS_RUCKSACK_RUCKSACK_HPP

#include <string_view>
#include <vector>

namespace Solutions::CheckRuckSacks {

class RuckSack
{
    public:

	RuckSack() = default;
	explicit RuckSack(std::string_view data) : m_ruckSackContents{data.begin(), data.end()} {}

	static constexpr auto
	charToPriority(char character) -> uint32_t
	{
	    constexpr auto uppercaseOffset = 26U;
	    const auto islowercase = static_cast<unsigned int>(std::islower(character) != 0);
	    const auto isuppercase = static_cast<unsigned int>(std::isupper(character) != 0);
	    return islowercase * uint32_t(character - 'a') + isuppercase * (uint32_t(character - 'A') + uppercaseOffset) + 1U;
	};

	void calculatePriority();

	[[nodiscard]] inline auto
	getPriority() const -> uint32_t
	{
	    return m_priority;
	}

	[[nodiscard]] inline auto
	getContents() const -> std::string
	{
	    return m_ruckSackContents;
	}

    private:

	std::string m_ruckSackContents{};
	uint32_t m_priority{};
};

[[nodiscard]] auto stringToRuckSacks(std::string_view input) -> std::vector<RuckSack>;

} // namespace Solutions::CheckRuckSacks
#endif