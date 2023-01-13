#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// Project wide definitions
#include <cstdint>
#include <ranges>
#include <string_view>
namespace utils {

constexpr ulong uintWidth = 32;
enum class SolutionId : ulong;

// Is this safe?
template<SolutionId... Values> class SolutionIdCheck
{
    public:

	template<typename IntType> static auto constexpr valueExists(IntType /*unused*/) -> bool { return false; }
};

template<SolutionId V, SolutionId... Next> class SolutionIdCheck<V, Next...> : private SolutionIdCheck<Next...>
{
	using super = SolutionIdCheck<Next...>;

    public:

	template<typename IntType> static auto constexpr valueExists(IntType val) -> bool
	{
	    return val == static_cast<IntType>(V) || super::valueExists(val);
	}
};

constexpr auto
dayAndProblemToComposite(uint32_t day, uint32_t problem) -> ulong
{
    return (ulong(day) << uintWidth) + ulong(problem);
}

enum class SolutionId : ulong
{
    FattestElfCalories = dayAndProblemToComposite(1, 1),
    TopThreeFattestElfCalories = dayAndProblemToComposite(1, 2),
    RockPaperScissors = dayAndProblemToComposite(2, 1),
    DecryptedRockPaperScissors = dayAndProblemToComposite(2, 2),
    RucksackReorganization = dayAndProblemToComposite(3, 1),
    RucksackBadges = dayAndProblemToComposite(3, 2),
    CampCleanup = dayAndProblemToComposite(4, 1),
    PartialCampCleanup = dayAndProblemToComposite(4, 2),
    RearrangeSupplyStacks = dayAndProblemToComposite(5, 1),
    RearrangeSupplyStacksWithAdvancedCrane = dayAndProblemToComposite(5, 2),
    TuningTrouble = dayAndProblemToComposite(6, 1),
    MessageTuningTrouble = dayAndProblemToComposite(6, 2),
    NoSpace = dayAndProblemToComposite(7, 1),
    YesSpace = dayAndProblemToComposite(7, 2),
    TreetopTreeHouse = dayAndProblemToComposite(8, 1),
    Invalid = 0
};

using IsValidSolution =
  SolutionIdCheck<SolutionId::FattestElfCalories, SolutionId::TopThreeFattestElfCalories, SolutionId::RockPaperScissors,
		  SolutionId::DecryptedRockPaperScissors, SolutionId::RucksackReorganization,
		  SolutionId::RucksackBadges, SolutionId::CampCleanup, SolutionId::PartialCampCleanup,
		  SolutionId::RearrangeSupplyStacks, SolutionId::RearrangeSupplyStacksWithAdvancedCrane,
		  SolutionId::TuningTrouble, SolutionId::MessageTuningTrouble, SolutionId::NoSpace,
		  SolutionId::YesSpace, SolutionId::TreetopTreeHouse>;

namespace SolutionIdStrings {
    constexpr auto FattestElfCalories = "FattestElfCalories";
    constexpr auto TopThreeFattestElfCalories = "TopThreeFattestElfCalories";
    constexpr auto RockPaperScissors = "RockPaperScissors";
    constexpr auto DecryptedRockPaperScissors = "DecryptedRockPaperScissors";
    constexpr auto RucksackReorganization = "RucksackReorganization";
    constexpr auto RucksackBadges = "RucksackBadges";
    constexpr auto CampCleanup = "CampCleanup";
    constexpr auto PartialCampCleanup = "PartialCampCleanup";
    constexpr auto RearrangeSupplyStacks = "RearrangeSupplyStacks";
    constexpr auto RearrangeSupplyStacksWithAdvancedCrane = "RearrangeSupplyStacksWithAdvancedCrane";
    constexpr auto TuningTrouble = "TuningTrouble";
    constexpr auto MessageTuningTrouble = "MessageTuningTrouble";
    constexpr auto NoSpace = "NoSpace";
    constexpr auto YesSpace = "YesSpace";
    constexpr auto TreetopTreeHouse = "TreetopTreeHouse";
    constexpr auto Invalid = "InvalidSolutionId";
} // namespace SolutionIdStrings

constexpr auto
SolutionIdToString(SolutionId solutionId) noexcept -> const char*
{
    using enum SolutionId;
    switch (solutionId)
	{
	    case FattestElfCalories:
		{
		    return SolutionIdStrings::FattestElfCalories;
		}
	    case TopThreeFattestElfCalories:
		{
		    return SolutionIdStrings::TopThreeFattestElfCalories;
		}
	    case RockPaperScissors:
		{
		    return SolutionIdStrings::RockPaperScissors;
		}
	    case DecryptedRockPaperScissors:
		{
		    return SolutionIdStrings::DecryptedRockPaperScissors;
		}
	    case RucksackReorganization:
		{
		    return SolutionIdStrings::RucksackReorganization;
		}
	    case RucksackBadges:
		{
		    return SolutionIdStrings::RucksackBadges;
		}
	    case CampCleanup:
		{
		    return SolutionIdStrings::CampCleanup;
		}
	    case PartialCampCleanup:
		{
		    return SolutionIdStrings::PartialCampCleanup;
		}
	    case RearrangeSupplyStacks:
		{
		    return SolutionIdStrings::RearrangeSupplyStacks;
		}
	    case RearrangeSupplyStacksWithAdvancedCrane:
		{
		    return SolutionIdStrings::RearrangeSupplyStacksWithAdvancedCrane;
		}
	    case TuningTrouble:
		{
		    return SolutionIdStrings::TuningTrouble;
		}
	    case MessageTuningTrouble:
		{
		    return SolutionIdStrings::MessageTuningTrouble;
		}
	    case NoSpace:
		{
		    return SolutionIdStrings::NoSpace;
		}
	    case YesSpace:
		{
		    return SolutionIdStrings::YesSpace;
		}
	    case TreetopTreeHouse:
		{
		    return SolutionIdStrings::TreetopTreeHouse;
		}
	    case Invalid:
		{
		    return SolutionIdStrings::Invalid;
		}
	}
}

} // namespace utils

#endif