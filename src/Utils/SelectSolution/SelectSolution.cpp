#include "SelectSolution.hpp"

#include <stdexcept>
#include <string>

auto toErrorFormat(int day, int problem) -> std::string
{
	return std::string("day: ") + std::to_string(day) + " problem: " + std::to_string(problem);
}

namespace utils {

auto SelectSolution(int day, int problem) -> SolutionId
{
	using enum utils::SolutionId;
	switch (day)
	{
	case 1:
	{
		if(problem == 1) {
			return FattestElfCalories;
		}
		if(problem == 2) {
			throw std::invalid_argument("Invalid argument: " + toErrorFormat(day, problem));
		}
		throw std::invalid_argument("Invalid argument: " + toErrorFormat(day, problem));
	}
	default:
		throw std::invalid_argument("Invalid argument: " + toErrorFormat(day, problem));
	}
}

} // namespace utils
