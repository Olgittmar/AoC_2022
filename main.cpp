// Internal utils
#include "PrettyPrint/PrettyPrint.hpp"

#include <Utils.hpp>

// Internal Solutions
#include <RunSolution.hpp>

// Std
#include <cstdlib>
#include <exception>
#include <experimental/source_location>
#include <iostream>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>

using utils::SelectSolution;
using utils::SelectSolutionData;

auto
main(int argCount, char* argv[]) -> int
{
    using source_location = std::experimental::source_location;

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
		    utils::log_error(source_location::current(), "Invalid solution id: ", uint32_t(solutionId), " from day: ", day, " and problem: ", problem);
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
		    utils::log_error(source_location::current(), "Something went wrong!");
		    return EXIT_FAILURE;
		}

    } catch (const std::invalid_argument& err)
	{
	    utils::log_error(source_location::current(), "Invalid argument: ", err.what());
	    return EXIT_FAILURE;
    } catch (const std::out_of_range& err)
	{
	    utils::log_error(source_location::current(), "Out of range exception: ", err.what());
	    return EXIT_FAILURE;
    } catch (const std::filesystem::filesystem_error& err)
	{
	    utils::log_error(source_location::current(), "Filesystem exception: ", err.what());
	    return EXIT_FAILURE;
    } catch (const std::exception& err)
	{
	    utils::log_error(source_location::current(), "Unknown exception: ", err.what());
	    return EXIT_FAILURE;
    } catch (...)
	{
	    utils::log_error(source_location::current(), "Unhandled exception!");
	    return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}