#ifndef SOLUTIONS_SUPPLYSTACKS_HPP
#define SOLUTIONS_SUPPLYSTACKS_HPP

#include <cstddef>
#include <string>
#include <string_view>

namespace Solutions {

constexpr size_t numStacksInDataSet = 9UL;
constexpr size_t numStacksInTestDataSet = 3UL;

template<size_t NumStacksInSupply>
auto GetCratesAtTopOfStacksAfterMoveOperations(const std::string_view& input, bool& success) -> std::string;

template<bool testRun = false>
auto
GetCratesAtTopOfEachStack(const std::string_view& input, bool& success) -> std::string
{
    if constexpr (testRun)
	{
	    // Why is it ok to instantiate the template within the scope of another template, but not at namespace
	    // scope?
	    return GetCratesAtTopOfStacksAfterMoveOperations<numStacksInTestDataSet>(input, success);
    } else
	{
	    return GetCratesAtTopOfStacksAfterMoveOperations<numStacksInDataSet>(input, success);
	}
}

template<size_t NumStacksInSupply>
auto GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane(const std::string_view& input, bool& success)
  -> std::string;

template<bool testRun = false>
auto
GetCratesAtTopOfEachStackWithAdvancedCrane(const std::string_view& input, bool& success) -> std::string
{
    if constexpr (testRun)
	{
	    return GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<numStacksInTestDataSet>(input, success);
    } else
	{
	    return GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<numStacksInDataSet>(input, success);
	}
}

// These should be separated per build target, but I can't be bothered right now.
template auto GetCratesAtTopOfEachStack<true>(const std::string_view& input, bool& success) -> std::string;
template auto GetCratesAtTopOfEachStack<false>(const std::string_view& input, bool& success) -> std::string;

template auto GetCratesAtTopOfEachStackWithAdvancedCrane<true>(const std::string_view& input, bool& success)
  -> std::string;
template auto GetCratesAtTopOfEachStackWithAdvancedCrane<false>(const std::string_view& input, bool& success)
  -> std::string;

} // namespace Solutions
#endif