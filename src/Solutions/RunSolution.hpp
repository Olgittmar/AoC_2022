#ifndef UTILS_RUNSOLUTION_RUNSOLUTION_HPP
#define UTILS_RUNSOLUTION_RUNSOLUTION_HPP

// utils
#include <Definitions.hpp>
#include <Utils.hpp>

// Internal
#include "CampCleanup/CampCleanup.hpp"
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

namespace Solutions {

template<bool testRun = false>
auto
runSolution(utils::SolutionId solutionId, const std::string_view& input, bool& success) -> std::string
{
    using enum utils::SolutionId;

    std::string result;
    try
	{
	    switch (solutionId)
		{
		    case FattestElfCalories:
			{
			    const auto calories = GetCaloriesOfElfWithMostCalories(input, success);
			    result = std::to_string(calories);
			    break;
			}
		    case TopThreeFattestElfCalories:
			{
			    const auto calories = GetCaloriesOfTopThreeElvesWithMostCalories(input, success);
			    result = std::to_string(calories);
			    break;
			}
		    case RockPaperScissors:
			{
			    const auto score = GetScoreOfStrategyGuide(input, success);
			    result = std::to_string(score);
			    break;
			}
		    case DecryptedRockPaperScissors:
			{
			    const auto score = GetScoreOfDecryptedStrategyGuide(input, success);
			    result = std::to_string(score);
			    break;
			}
		    case RucksackReorganization:
			{
			    const auto sum = GetSumOfCompartmentItemTypePriority(input, success);
			    result = std::to_string(sum);
			    break;
			}
		    case RucksackBadges:
			{
			    const auto sum = GetSumOfAuthenticityBadges(input, success);
			    result = std::to_string(sum);
			    break;
			}
		    case CampCleanup:
			{
			    const auto sum = GetNumRedundantAssignmentPairs(input, success);
			    result = std::to_string(sum);
			    break;
			}
		    case PartialCampCleanup:
			{
			    const auto sum = GetNumPartiallyRedundantAssignmentPairs(input, success);
			    result = std::to_string(sum);
			    break;
			}
		    case RearrangeSupplyStacks:
			{
			    std::string crateIds;
			    if constexpr (testRun)
				{
				    result =
				      GetCratesAtTopOfStacksAfterMoveOperations<SupplyStacks::numStacksInTestDataSet>(
					input, success);
			    } else
				{
				    result =
				      GetCratesAtTopOfStacksAfterMoveOperations<SupplyStacks::numStacksInDataSet>(
					input, success);
				}
			    break;
			}
		    case RearrangeSupplyStacksWithAdvancedCrane:
			{
			    std::string crateIds;
			    if constexpr (testRun)
				{
				    result = GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<
				      SupplyStacks::numStacksInTestDataSet>(input, success);
			    } else
				{
				    result = GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<
				      SupplyStacks::numStacksInDataSet>(input, success);
				}
			    break;
			}
		    case TuningTrouble:
			{
			    const auto numChars = GetNumCharactersBeforeStartOfPacket(input, success);
			    result = std::to_string(numChars);
			    break;
			}
		    case MessageTuningTrouble:
			{
			    const auto numChars = GetNumCharactersBeforeStartOfMessage(input, success);
			    result = std::to_string(numChars);
			    break;
			}
		    case NoSpace:
			{
			    const auto totalSize =
			      GetTotalSizeOfDirectories<size_t, NoSpace::dirSizeLimit>(input, success);
			    result = std::to_string(totalSize);
			    break;
			}
		    case YesSpace:
			{
			    const auto sizeOfDirToDelete =
			      GetSizeOfDirectoryToDelete<size_t, NoSpace::availableSpaceOnFilesystem,
							 NoSpace::spaceOnFilesystemRequired>(input, success);
			    result = std::to_string(sizeOfDirToDelete);
			    break;
			}
		    case TreetopTreeHouse:
			{
			    if constexpr (testRun)
				{
				    const auto numTreesVisible = GetNumTreesVisibleFromOutsideForest<
				      size_t, utils::index_t{TreetopTreeHouse::NumTreeRowsInTest,
							     TreetopTreeHouse::NumTreeColumnsInTest}>(input, success);

				    result = std::to_string(numTreesVisible);
			    } else
				{
				    const auto numTreesVisible = GetNumTreesVisibleFromOutsideForest<
				      size_t, utils::index_t{TreetopTreeHouse::NumTreeRows,
							     TreetopTreeHouse::NumTreeColumns}>(input, success);

				    result = std::to_string(numTreesVisible);
				}
			    break;
			}
		    case TreetopTreeHouseDist:
			{
			    if constexpr (testRun)
				{
				    const auto visibilityScore = GetVisibilityScoreOfHighestScoringTree<
				      size_t, utils::index_t{TreetopTreeHouse::NumTreeRowsInTest,
							     TreetopTreeHouse::NumTreeColumnsInTest}>(input, success);

				    result = std::to_string(visibilityScore);
			    } else
				{
				    const auto visibilityScore = GetVisibilityScoreOfHighestScoringTree<
				      size_t, utils::index_t{TreetopTreeHouse::NumTreeRows,
							     TreetopTreeHouse::NumTreeColumns}>(input, success);

				    result = std::to_string(visibilityScore);
				}
			    break;
			}
		    case RopeBridge:
			{
			    const auto numPositionsVisited = GetNumPositionsVisitedByTail<2>(input, success);

			    result = std::to_string(numPositionsVisited);
			    break;
			}
		    case Invalid:
			{
			    result = "runSolution(): Invalid solutionId";
			    break;
			}
		}

    } catch (const std::exception& err)
	{
	    // TODO: add proper exception handling
	    utils::log_error(std::experimental::source_location::current(), err.what());
	    result = "runSolution(): Encountered exception: " + std::string(err.what());
    } catch (...)
	{
	    utils::log_error(std::experimental::source_location::current(), "Unhandled exception");
	    result = "runSolution(): Encountered unhandled exception!";
    }

    return result;
}

} // namespace Solutions
#endif