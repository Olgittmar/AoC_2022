// Internal utils
#include "Definitions.hpp"
#include "SelectSolution/SelectSolution.hpp"

#include <Utils.hpp>

// Internal Solutions
#include <ElfCalories.hpp>
#include <RockPaperScissors.hpp>
#include <RuckSack.hpp>
#include <RunSolution.hpp>
// Std
#include <cstdlib>
#include <exception>
#include <iostream>
#include <span>
#include <string>
#include <string_view>

auto
main(int argCount, char* argv[]) -> int
{
    const auto args = std::span(argv, size_t(argCount));
    if (args.size() < 3) {
	    return EXIT_FAILURE;
	}

    uint32_t day = 0;
    uint32_t problem = 0;

    try {
	    const auto problemIndex = args.subspan(1, 2);
	    // TODO: Don't allow wierd input
	    auto* const dayStr = problemIndex.front();
	    auto* const problemStr = problemIndex.back();

	    // TODO: Safe?
	    day = std::stoul(dayStr);
	    if (day < 1 || day > utils::daysSolved) {
		    std::cout << "Invalid day index:" << dayStr << std::endl;
		    return EXIT_FAILURE;
		}

	    problem = std::stoul(problemStr);
	    if (problem < 1 || problem > utils::problemsPerDay) {
		    std::cout << "Invalid problem index: " << problemStr << std::endl;
		    return EXIT_FAILURE;
		}

	    for (const auto& arg : args.subspan(3)) {
		    // whatever arguments are left
		}

	    bool success = false;
	    const auto solutionId = utils::SelectSolution(day, problem);
	    if (solutionId == utils::SolutionId::Invalid) {
		    std::cout << "Invalid solution id: " << uint32_t(solutionId) << std::endl;
		    return EXIT_FAILURE;
		}
	    const auto solutionDataId = utils::SelectSolutionData(solutionId);
	    const auto input = utils::DataBroker::getSolutionData(solutionDataId);
	    const auto result = Solutions::runSolution(solutionId, input, success);

	    if (success) {
		    // TODO: Gotta fix some kind of logging framework...
		    std::cout << result << std::endl;
		}
	    else {
		    std::cout << "Something went wrong!" << std::endl;
		    return EXIT_FAILURE;
		}

    } catch (const std::invalid_argument& err) {
	    std::cout << err.what() << std::endl;
	    return EXIT_FAILURE;
    } catch (const std::filesystem::filesystem_error& err) {
	    std::cout << err.what() << std::endl;
	    return EXIT_FAILURE;
    } catch (const std::exception& err) {
	    std::cout << err.what() << std::endl;
	    return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}