#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// Project wide definitions
#include <cstddef>
#include <cstdint>
#include <ranges>
#include <string_view>

// Project internal
#include "Coordinates/Coordinates2D.hpp"

namespace utils {

using index_t = utils::Index2D<size_t>;

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
    TreetopTreeHouseDist = dayAndProblemToComposite(8, 2),
    RopeBridge = dayAndProblemToComposite(9, 1),
    RopeBridgeWithLongRopes = dayAndProblemToComposite(9, 2),
    Invalid = 0
};

using IsValidSolution =
  SolutionIdCheck<SolutionId::FattestElfCalories, SolutionId::TopThreeFattestElfCalories, SolutionId::RockPaperScissors,
		  SolutionId::DecryptedRockPaperScissors, SolutionId::RucksackReorganization,
		  SolutionId::RucksackBadges, SolutionId::CampCleanup, SolutionId::PartialCampCleanup,
		  SolutionId::RearrangeSupplyStacks, SolutionId::RearrangeSupplyStacksWithAdvancedCrane,
		  SolutionId::TuningTrouble, SolutionId::MessageTuningTrouble, SolutionId::NoSpace,
		  SolutionId::YesSpace, SolutionId::TreetopTreeHouse, SolutionId::TreetopTreeHouseDist,
		  SolutionId::RopeBridge, SolutionId::RopeBridgeWithLongRopes>;

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
    constexpr auto TreetopTreeHouseDist = "TreetopTreeHouseDist";
    constexpr auto RopeBridge = "RopeBridge";
    constexpr auto RopeBridgeWithLongRopes = "RopeBridgeWithLongRopes";
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
	    case TreetopTreeHouseDist:
		{
		    return SolutionIdStrings::TreetopTreeHouseDist;
		}
	    case RopeBridge:
		{
		    return SolutionIdStrings::RopeBridge;
		}
	    case RopeBridgeWithLongRopes:
		{
		    return SolutionIdStrings::RopeBridgeWithLongRopes;
		}
	    case Invalid:
		{
		    return SolutionIdStrings::Invalid;
		}
	}
}

namespace Color {
    // Reset
    constexpr auto RESET = "\033[0m"; // Text Reset

    namespace Foreground {
	// Regular Colors
	constexpr auto BLACK = "\033[0;30m";  // BLACK
	constexpr auto RED = "\033[0;31m";    // RED
	constexpr auto GREEN = "\033[0;32m";  // GREEN
	constexpr auto YELLOW = "\033[0;33m"; // YELLOW
	constexpr auto BLUE = "\033[0;34m";   // BLUE
	constexpr auto PURPLE = "\033[0;35m"; // PURPLE
	constexpr auto CYAN = "\033[0;36m";   // CYAN
	constexpr auto WHITE = "\033[0;37m";  // WHITE

	// Bold
	constexpr auto BLACK_BOLD = "\033[1;30m";  // BLACK
	constexpr auto RED_BOLD = "\033[1;31m";    // RED
	constexpr auto GREEN_BOLD = "\033[1;32m";  // GREEN
	constexpr auto YELLOW_BOLD = "\033[1;33m"; // YELLOW
	constexpr auto BLUE_BOLD = "\033[1;34m";   // BLUE
	constexpr auto PURPLE_BOLD = "\033[1;35m"; // PURPLE
	constexpr auto CYAN_BOLD = "\033[1;36m";   // CYAN
	constexpr auto WHITE_BOLD = "\033[1;37m";  // WHITE

	// Underline
	constexpr auto BLACK_UNDERLINED = "\033[4;30m";  // BLACK
	constexpr auto RED_UNDERLINED = "\033[4;31m";    // RED
	constexpr auto GREEN_UNDERLINED = "\033[4;32m";  // GREEN
	constexpr auto YELLOW_UNDERLINED = "\033[4;33m"; // YELLOW
	constexpr auto BLUE_UNDERLINED = "\033[4;34m";   // BLUE
	constexpr auto PURPLE_UNDERLINED = "\033[4;35m"; // PURPLE
	constexpr auto CYAN_UNDERLINED = "\033[4;36m";   // CYAN
	constexpr auto WHITE_UNDERLINED = "\033[4;37m";  // WHITE

	namespace HighIntensity {

	    // High Intensity
	    constexpr auto BLACK_BRIGHT = "\033[0;90m";  // BLACK
	    constexpr auto RED_BRIGHT = "\033[0;91m";    // RED
	    constexpr auto GREEN_BRIGHT = "\033[0;92m";  // GREEN
	    constexpr auto YELLOW_BRIGHT = "\033[0;93m"; // YELLOW
	    constexpr auto BLUE_BRIGHT = "\033[0;94m";   // BLUE
	    constexpr auto PURPLE_BRIGHT = "\033[0;95m"; // PURPLE
	    constexpr auto CYAN_BRIGHT = "\033[0;96m";   // CYAN
	    constexpr auto WHITE_BRIGHT = "\033[0;97m";  // WHITE

	    // Bold High Intensity
	    constexpr auto BLACK_BOLD_BRIGHT = "\033[1;90m";  // BLACK
	    constexpr auto RED_BOLD_BRIGHT = "\033[1;91m";    // RED
	    constexpr auto GREEN_BOLD_BRIGHT = "\033[1;92m";  // GREEN
	    constexpr auto YELLOW_BOLD_BRIGHT = "\033[1;93m"; // YELLOW
	    constexpr auto BLUE_BOLD_BRIGHT = "\033[1;94m";   // BLUE
	    constexpr auto PURPLE_BOLD_BRIGHT = "\033[1;95m"; // PURPLE
	    constexpr auto CYAN_BOLD_BRIGHT = "\033[1;96m";   // CYAN
	    constexpr auto WHITE_BOLD_BRIGHT = "\033[1;97m";  // WHITE

	} // namespace HighIntensity
    }     // namespace Foreground

    namespace Background {

	// Background
	constexpr auto BLACK_BACKGROUND = "\033[40m";  // BLACK
	constexpr auto RED_BACKGROUND = "\033[41m";    // RED
	constexpr auto GREEN_BACKGROUND = "\033[42m";  // GREEN
	constexpr auto YELLOW_BACKGROUND = "\033[43m"; // YELLOW
	constexpr auto BLUE_BACKGROUND = "\033[44m";   // BLUE
	constexpr auto PURPLE_BACKGROUND = "\033[45m"; // PURPLE
	constexpr auto CYAN_BACKGROUND = "\033[46m";   // CYAN
	constexpr auto WHITE_BACKGROUND = "\033[47m";  // WHITE

	namespace HighIntensity {

	    // High Intensity backgrounds
	    constexpr auto BLACK_BACKGROUND_BRIGHT = "\033[0;100m";  // BLACK
	    constexpr auto RED_BACKGROUND_BRIGHT = "\033[0;101m";    // RED
	    constexpr auto GREEN_BACKGROUND_BRIGHT = "\033[0;102m";  // GREEN
	    constexpr auto YELLOW_BACKGROUND_BRIGHT = "\033[0;103m"; // YELLOW
	    constexpr auto BLUE_BACKGROUND_BRIGHT = "\033[0;104m";   // BLUE
	    constexpr auto PURPLE_BACKGROUND_BRIGHT = "\033[0;105m"; // PURPLE
	    constexpr auto CYAN_BACKGROUND_BRIGHT = "\033[0;106m";   // CYAN
	    constexpr auto WHITE_BACKGROUND_BRIGHT = "\033[0;107m";  // WHITE

	} // namespace HighIntensity

    } // namespace Background

} // namespace Color

} // namespace utils

namespace Solutions {
namespace NoSpace {

    constexpr size_t dirSizeLimit = 100000;
    constexpr size_t availableSpaceOnFilesystem = 70000000;
    constexpr size_t spaceOnFilesystemRequired = 30000000;

    constexpr auto RootName = "/";
} // namespace NoSpace

namespace SupplyStacks {
    constexpr size_t numStacksInDataSet = 9UL;
    constexpr size_t numStacksInTestDataSet = 3UL;
} // namespace SupplyStacks

namespace CheckRuckSacks {
    constexpr size_t numRucksacksInGroup = 3;
} // namespace CheckRuckSacks

namespace TreetopTreeHouse {
    constexpr size_t NumTreeRowsInTest = 5;
    constexpr size_t NumTreeColumnsInTest = 5;

    constexpr size_t NumTreeRows = 99;
    constexpr size_t NumTreeColumns = 99;

    constexpr size_t highestTreePossible = 9;
} // namespace TreetopTreeHouse

namespace RopeBridge {
    using LengthType_t = long;
    using DistType_t = unsigned short;
    using PositionHash_t = utils::Coordinate2DHash<LengthType_t>;

    constexpr size_t ShortRopeLength = 2;
    constexpr size_t LongRopeLength = 10;
} // namespace RopeBridge

} // namespace Solutions

#endif