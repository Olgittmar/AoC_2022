#include "SelectSolution.hpp"

#include <stdexcept>
#include <string>

namespace {
auto
toErrorFormat(uint32_t day, uint32_t problem) -> std::string
{
    return std::string("day: ") + std::to_string(day) + " problem: " + std::to_string(problem);
}
} // namespace
namespace utils {

auto
SelectSolution(uint32_t day, uint32_t problem) -> SolutionId
{
    using enum utils::SolutionId;
    if (day == 1) {
	    if (problem == 1) {
		    return FattestElfCalories;
	    }
	    if (problem == 2) {
		    return TopThreeFattestElfCalories;
	    }
    } else if (day == 1) {
	    if (problem == 1) {
		    return RockPaperScissors;
	    }
    }

    throw std::invalid_argument("Invalid argument: " + toErrorFormat(day, problem));
}

} // namespace utils
