#include "DataBroker/DataBroker.hpp"
#include "Definitions.hpp"
#include "ElfCalories.hpp"
#include "SelectSolution/SelectSolution.hpp"

#include <Utils.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <span>
#include <string>
#include <string_view>

auto
runSolution(int day, int problem, bool& success) -> std::string
{
    const auto solutionId = utils::SelectSolution(day, problem);
    const auto input = utils::DataBroker::getSolutionData(solutionId); // get input from DataBroker

    using enum utils::SolutionId;
    switch (solutionId) {
	case FattestElfCalories:
	{
	    const auto calories = Solutions::GetCaloriesOfElfWithMostCalories(input, success);
	    return std::to_string(calories);
	}
	case Invalid:
	    return "Invalid solutionId";
    }
}

auto
main(int argCount, char* argv[]) -> int
{
    const auto args = std::span(argv, size_t(argCount));
    if (args.size() < 2) {
	return EXIT_FAILURE;
    }

    const auto problemIndex = args.subspan(0, 2);
    // TODO: Don't allow wierd input
    std::string dayStr = problemIndex.front();
    std::string problemStr = problemIndex.back();

    // TODO: Safe?
    int day = std::stoi(dayStr);
    if (day < 1 || day > utils::daysSolved) {
	std::cout << "Invalid day:" << dayStr << std::endl;
	return EXIT_FAILURE;
    }

    int problem = std::stoi(problemStr);
    if (problem < 1 || problem > utils::problemsPerDay) {
	std::cout << "Invalid problem: " << problemStr << std::endl;
	return EXIT_FAILURE;
    }

    for (const auto& arg : args.subspan(2)) {
	// whatever arguments are left
    }

    bool success = false;
    try {
	const auto result = runSolution(day, problem, success);

	if (success) {
	    // TODO: Gotta fix some kind of logging framework...
	    std::cout << result << std::endl;
	} else {
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