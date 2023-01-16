#ifndef SOLUTIONS_RUCKSACK_RUCKSACKGROUP_HPP
#define SOLUTIONS_RUCKSACK_RUCKSACKGROUP_HPP

// Std
#include <cstddef>
#include <string_view>
#include <vector>

// Internal
#include "RuckSack.hpp"

namespace Solutions::CheckRuckSacks {

template<size_t NumSacksInGroup> class RuckSackGroup
{
    public:

	// Use range as parameter instead?
	explicit RuckSackGroup(const std::vector<RuckSack>::const_iterator& start,
			       const std::vector<RuckSack>::const_iterator& stop);

	[[nodiscard]] auto getPriorityOfAuthenticityBadge() const -> uint32_t;

    private:

	// Generalize for arbitrary grouping
	std::vector<std::string> m_contents{};
};

template<size_t NumSacksInGroup>
auto stringToRuckSackGroups(const std::string_view& input) -> std::vector<RuckSackGroup<NumSacksInGroup>>;

} // namespace Solutions::CheckRuckSacks
#endif