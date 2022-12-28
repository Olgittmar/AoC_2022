// Internal utils
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

using utils::SelectSolution;
using utils::SelectSolutionData;

auto
main(int argCount, char* argv[]) -> int
{
    const auto args = std::span(argv, size_t(argCount));
    if (args.size() < 3)
	{
	    return EXIT_FAILURE;
    }

    uint32_t day = 0;
    uint32_t problem = 0;

    try
	{
	    const auto problemIndex = args.subspan(1, 2);
	    // TODO: Don't allow wierd input
	    auto* const dayStr = problemIndex.front();
	    auto* const problemStr = problemIndex.back();

	    // TODO: Safe?
	    day = std::stoul(dayStr);
	    problem = std::stoul(problemStr);

	    // for (const auto& arg : args.subspan(3)) {
	    //     // whatever arguments are left
	    // }

	    const auto solutionId = SelectSolution(day, problem);
	    if (solutionId == utils::SolutionId::Invalid)
		{
		    std::cout << "Invalid solution id: " << uint32_t(solutionId) << std::endl;
		    return EXIT_FAILURE;
	    }

	    const auto solutionDataId = SelectSolutionData(solutionId);
	    const auto input = utils::DataBroker::getSolutionData(solutionDataId);

	    bool success = false;
	    const auto result = Solutions::runSolution(solutionId, input, success);

	    if (success)
		{
		    // TODO: Gotta fix some kind of logging framework...
		    std::cout << result << std::endl;
	    } else
		{
		    std::cout << "Something went wrong!" << std::endl;
		    return EXIT_FAILURE;
		}

    } catch (const std::invalid_argument& err)
	{
	    std::cout << err.what() << std::endl;
	    return EXIT_FAILURE;
    } catch (const std::filesystem::filesystem_error& err)
	{
	    std::cout << err.what() << std::endl;
	    return EXIT_FAILURE;
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
	    return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}