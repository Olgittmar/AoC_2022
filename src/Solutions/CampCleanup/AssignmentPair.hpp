#ifndef SOLUTIONS_CAMPCLEANUP_ASSIGNMENTPAIR_HPP
#define SOLUTIONS_CAMPCLEANUP_ASSIGNMENTPAIR_HPP

#include <string_view>
#include <vector>

namespace Solutions::CampCleanup {

struct CleanupSection
{
	// uint32_t ID = 0;

	struct Range
	{
		uint32_t start = 0;
		uint32_t end = 0;
	} range;
};

struct AssignmentPair
{
	[[nodiscard]] auto fullyOverlaps() const -> bool;
	[[nodiscard]] auto partiallyOverlaps() const -> bool;

	CleanupSection first;
	CleanupSection second;
};

auto stringToAssignmentPairs(std::string_view input) -> std::vector<AssignmentPair>;

} // namespace Solutions::CampCleanup
#endif
