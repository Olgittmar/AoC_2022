#ifndef UTILS_RUNSOLUTION_RUNSOLUTION_HPP
#define UTILS_RUNSOLUTION_RUNSOLUTION_HPP

// utils
#include <Utils.hpp>

// Internal
#include "CampCleanup.hpp"
#include "ElfCalories.hpp"
#include "NoSpace.hpp"
#include "RockPaperScissors.hpp"
#include "RuckSack.hpp"
#include "SupplyStacks.hpp"
#include "TreetopTreeHouse.hpp"
#include "TuningTrouble.hpp"

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
				      GetCratesAtTopOfStacksAfterMoveOperations<numStacksInTestDataSet>(input, success);
			    } else
				{
				    result =
				      GetCratesAtTopOfStacksAfterMoveOperations<numStacksInDataSet>(input, success);
				}
			    break;
			}
		    case RearrangeSupplyStacksWithAdvancedCrane:
			{
			    std::string crateIds;
			    if constexpr (testRun)
				{
				    result = GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<
				      numStacksInTestDataSet>(input, success);
			    } else
				{
				    result =
				      GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<numStacksInDataSet>(
					input, success);
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
			      GetTotalSizeOfDirectories<size_t, Solutions::dirSizeLimit>(input, success);
			    result = std::to_string(totalSize);
			    break;
			}
		    case YesSpace:
			{
			    const auto sizeOfDirToDelete =
			      GetSizeOfDirectoryToDelete<size_t, availableSpaceOnFilesystem, spaceOnFilesystemRequired>(
				input, success);
			    result = std::to_string(sizeOfDirToDelete);
			    break;
			}
		    case TreetopTreeHouse:
			{
			    if constexpr (testRun)
				{
				    const auto numTreesVisible =
				      GetNumTreesVisibleFromOutsideForest<size_t, NumTreeRowsInTest,
									  NumTreeColumnsInTest>(input, success);

				    result = std::to_string(numTreesVisible);
			    } else
				{
				    const auto numTreesVisible =
				      GetNumTreesVisibleFromOutsideForest<size_t, NumTreeRows, NumTreeColumns>(input,
													       success);

				    result = std::to_string(numTreesVisible);
				}
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
	    std::cout << err.what() << std::endl;
	    result = "runSolution(): Encountered exception: " + std::string(err.what());
    } catch (...)
	{
	    std::cout << "Unhandled exception!" << std::endl;
	    result = "runSolution(): Encountered unhandled exception!";
    }

    return result;
}

} // namespace Solutions
#endif