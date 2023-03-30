#ifndef UTILS_DATABROKER_TESTDATAGENERATOR_HPP
#define UTILS_DATABROKER_TESTDATAGENERATOR_HPP

#include <Definitions.hpp>
#include <algorithm>
#include <array>
#include <cstddef>
#include <random>
#include <string>

namespace utils {

template<size_t Severity> class TestDataGenerator
{
    public:

	template<SolutionId SolutionId> static auto generateTestData() -> std::string;

	template<>
	auto
	generateTestData<SolutionId::FattestElfCalories>() -> std::string
	{
	    std::string _ret;
	    constexpr auto lineDelimiter = "\n";
	    constexpr auto caloryMultiplier = 1000UL;

	    for (size_t inventoryIdx = 0; inventoryIdx < Severity; ++inventoryIdx)
		{
		    const auto inventory = getRandomDistribution(1UL, caloryMultiplier * Severity);
		    for (auto inventoryLine : inventory)
			{
			    _ret.append(std::to_string(inventoryLine) + lineDelimiter);
			}

		    if (inventoryIdx + 1 < Severity)
			{
			    _ret.append(lineDelimiter);
		    }
		}

	    return _ret;
	}

	template<>
	auto
	generateTestData<SolutionId::RockPaperScissors>() -> std::string
	{
	    std::string _ret;
	    constexpr auto lineDelimiter = "\n";
	    constexpr size_t numOptions = 3UL;
	    constexpr size_t linesMultiplier = 100UL;
	    constexpr std::array<char, numOptions> firstOptions{'A', 'B', 'C'};
	    constexpr std::array<char, numOptions> secondOptions{'X', 'Y', 'Z'};

	    for (size_t round = 0; round < (Severity * linesMultiplier); ++round)
		{
		    const auto firstSelector = getRandomVal(0UL, numOptions - 1UL);
		    const auto secondSelector = getRandomVal(0UL, numOptions - 1UL);
		    _ret += firstOptions.at(firstSelector);
		    _ret.append(" ");
		    _ret += secondOptions.at(secondSelector);
		    _ret.append(lineDelimiter);
		}

	    return _ret;
	}

    private:

	template<typename IntegerType>
	static auto
	getRandomVal(IntegerType minVal, IntegerType maxVal)
	{
	    std::uniform_int_distribution<> distribution(minVal, maxVal);
	    std::random_device randDevice;
	    std::mt19937 generator{randDevice()};
	    return distribution(generator);
	}

	template<typename IntegerType>
	static auto
	getRandomDistribution(IntegerType minVal, IntegerType maxVal)
	{
	    std::array<IntegerType, Severity> _ret{};
	    std::generate(_ret.begin(), _ret.end(), [&]() { return getRandomVal(minVal, maxVal); });
	    return _ret;
	}
};

template class TestDataGenerator<utils::BenchmarkSolutions::BenchCaseSeverity>;

} // namespace utils

#endif