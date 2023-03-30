#ifndef UTILS_RUNSOLUTION_RUNSOLUTION_HPP
#define UTILS_RUNSOLUTION_RUNSOLUTION_HPP

// utils
#include <Utils.hpp>

// Internal
#include "CampCleanup/CampCleanup.hpp"
#include "CathodeRayTube/CathodeRayTube.hpp"
#include "ElfCalories/ElfCalories.hpp"
#include "NoSpace/NoSpace.hpp"
#include "PrettyPrint/PrettyPrint.hpp"
#include "RockPaperScissors/RockPaperScissors.hpp"
#include "RopeBridge/RopeBridge.hpp"
#include "RuckSack/CheckRuckSacks.hpp"
#include "SupplyStacks/SupplyStacks.hpp"
#include "TreetopTreeHouse/TreetopTreeHouse.hpp"
#include "TuningTrouble/TuningTrouble.hpp"

// Std
#include <iostream>
#include <string>
#include <string_view>
#include <variant>

namespace Solutions {
using ResultType_t = std::variant<std::string, short, int, long, unsigned short, unsigned int, unsigned long>;

struct ResultTypeToStringConverter
{
	auto
	operator()(const std::string& value) -> std::string
	{
	    return value;
	}

	auto
	operator()(long value) -> std::string
	{
	    return std::to_string(value);
	}

	auto
	operator()(int value) -> std::string
	{
	    return std::to_string(value);
	}

	auto
	operator()(short value) -> std::string
	{
	    return std::to_string(value);
	}

	auto
	operator()(unsigned long value) -> std::string
	{
	    return std::to_string(value);
	}

	auto
	operator()(unsigned int value) -> std::string
	{
	    return std::to_string(value);
	}

	auto
	operator()(unsigned short value) -> std::string
	{
	    return std::to_string(value);
	}
};

auto
ResultTypeToString(const ResultType_t& input) -> std::string
{
    return std::visit(ResultTypeToStringConverter{}, input);
}

template<bool testRun>
auto
getSolutionRunner(utils::SolutionId solutionId) -> std::function<ResultType_t(std::string_view, bool&)>
{
    using enum utils::SolutionId;
    switch (solutionId)
	{
	    case FattestElfCalories:
		{
		    return GetCaloriesOfElfWithMostCalories;
		}
	    case TopThreeFattestElfCalories:
		{
		    return GetCaloriesOfTopThreeElvesWithMostCalories;
		}
	    case RockPaperScissors:
		{
		    return GetScoreOfStrategyGuide;
		}
	    case DecryptedRockPaperScissors:
		{
		    return GetScoreOfDecryptedStrategyGuide;
		}
	    case RucksackReorganization:
		{
		    return GetSumOfCompartmentItemTypePriority;
		}
	    case RucksackBadges:
		{
		    return GetSumOfAuthenticityBadges;
		}
	    case CampCleanup:
		{
		    return GetNumRedundantAssignmentPairs;
		}
	    case PartialCampCleanup:
		{
		    return GetNumPartiallyRedundantAssignmentPairs;
		}
	    case RearrangeSupplyStacks:
		{
		    if constexpr (testRun)
			{
			    return GetCratesAtTopOfStacksAfterMoveOperations<SupplyStacks::numStacksInTestDataSet>;
		    } else
			{
			    return GetCratesAtTopOfStacksAfterMoveOperations<SupplyStacks::numStacksInDataSet>;
			}
		}
	    case RearrangeSupplyStacksWithAdvancedCrane:
		{
		    if constexpr (testRun)
			{
			    return GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<SupplyStacks::numStacksInTestDataSet>;
		    } else
			{
			    return GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<SupplyStacks::numStacksInDataSet>;
			}
		}
	    case TuningTrouble:
		{
		    return GetNumCharactersBeforeStartOfPacket;
		}
	    case MessageTuningTrouble:
		{
		    return GetNumCharactersBeforeStartOfMessage;
		}
	    case NoSpace:
		{
		    return GetTotalSizeOfDirectories<size_t, NoSpace::dirSizeLimit>;
		}
	    case YesSpace:
		{
		    return GetSizeOfDirectoryToDelete<size_t, NoSpace::availableSpaceOnFilesystem, NoSpace::spaceOnFilesystemRequired>;
		}
	    case TreetopTreeHouse:
		{
		    if constexpr (testRun)
			{
			    return GetNumTreesVisibleFromOutsideForest<size_t, utils::index_t{TreetopTreeHouse::NumTreeRowsInTest,
											      TreetopTreeHouse::NumTreeColumnsInTest}>;
		    } else
			{
			    return GetNumTreesVisibleFromOutsideForest<size_t, utils::index_t{TreetopTreeHouse::NumTreeRows, TreetopTreeHouse::NumTreeColumns}>;
			}
		}
	    case TreetopTreeHouseDist:
		{
		    if constexpr (testRun)
			{
			    return GetVisibilityScoreOfHighestScoringTree<size_t, utils::index_t{TreetopTreeHouse::NumTreeRowsInTest,
												 TreetopTreeHouse::NumTreeColumnsInTest}>;
		    } else
			{
			    return GetVisibilityScoreOfHighestScoringTree<size_t,
									  utils::index_t{TreetopTreeHouse::NumTreeRows, TreetopTreeHouse::NumTreeColumns}>;
			}
		}
	    case RopeBridge:
		{
		    return GetNumPositionsVisitedByTail<RopeBridge::ShortRopeLength>;
		}
	    case RopeBridgeWithLongRopes:
		{
		    return GetNumPositionsVisitedByTail<RopeBridge::LongRopeLength>;
		}
	    case CathodeRayTube:
		{
		    return GetSumOfSignalStrengths<CathodeRayTube::CycleOffset, CathodeRayTube::CycleStep, CathodeRayTube::CycleEnd>;
		}
	    case Invalid:
		{
		    return [](std::string_view data, bool& success) -> std::string { return "runSolution(): Invalid solutionId"; };
		}
	}
}

template<bool testRun = false>
auto
runSolution(utils::SolutionId solutionId, std::string_view input, bool& success) -> std::string
{
    using enum utils::SolutionId;
    std::string resultStr;

    try
	{
	    auto solutionRunner = getSolutionRunner<testRun>(solutionId);
	    const auto result = solutionRunner(input, success);
	    resultStr = ResultTypeToString(result);

    } catch (const std::exception& err)
	{
	    // TODO: add proper exception handling
	    utils::log_error(std::experimental::source_location::current(), err.what());
	    resultStr = "runSolution(): Encountered exception: " + std::string(err.what());
    } catch (...)
	{
	    utils::log_error(std::experimental::source_location::current(), "Unhandled exception");
	    resultStr = "runSolution(): Encountered unhandled exception!";
    }

    return resultStr;
}

} // namespace Solutions
#endif