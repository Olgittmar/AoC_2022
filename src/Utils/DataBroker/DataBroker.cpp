#include "DataBroker.hpp"

#include "SelectSolution/SelectSolution.hpp"
#include "TestDataGenerator.hpp"

#include <Definitions.hpp>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <system_error>

constexpr auto dataFolder = "data";
constexpr auto dataFileEnding = ".txt";

namespace utils {

auto
DataBroker::getSolutionData(SolutionId solutionId) -> std::string
{
    const auto filePath = getDataFileFullPath(solutionId);
    return getDataFromFile(filePath);
}

auto
DataBroker::getSolutionTestData(SolutionId solutionId, uint32_t testCase) -> std::string
{
    static std::map<std::pair<SolutionId, uint32_t>, std::string> dataCache;
    const std::pair<SolutionId, uint32_t> key{solutionId, testCase};

    if (!dataCache.contains(key))
	{
	    const auto filePath = getTestDataFileFullPath(solutionId, testCase);
	    dataCache[key] = getDataFromFile(filePath);
    }

    return dataCache.at(key);
}

auto
DataBroker::getSolutionBenchmarkDataGenerator(SolutionId solutionId) -> std::function<std::string()>
{
    using TestDataGenerator_t = TestDataGenerator<utils::BenchmarkSolutions::BenchCaseSeverity>;

    switch (solutionId)
	{
	    case SolutionId::FattestElfCalories:
	    case SolutionId::TopThreeFattestElfCalories:
		{
		    return TestDataGenerator_t::generateTestData<SolutionId::FattestElfCalories>;
		}
	    case SolutionId::RockPaperScissors:
	    case SolutionId::DecryptedRockPaperScissors:
		{
		    return TestDataGenerator_t::generateTestData<SolutionId::RockPaperScissors>;
		}
	    default:
		{
		    const auto solutionDataId = SelectSolutionData(solutionId);
		    return [solutionDataId]() { return getSolutionTestData(solutionDataId, 0); };
		}
	}
}

auto
DataBroker::getDataFileFullPath(SolutionId solutionId) -> std::filesystem::path
{
    auto path = std::filesystem::current_path();
    path /= dataFolder;
    path /= SolutionIdToString(solutionId);
    path += dataFileEnding;

    if (std::filesystem::exists(path))
	{
	    return path;
    }

    // Just throw an exception if we're trying to get a nonexisting file
    const auto errc = std::make_error_code(std::errc::no_such_file_or_directory);
    throw std::filesystem::filesystem_error("File not found: ", path, errc);
}

auto
DataBroker::getTestDataFileFullPath(SolutionId solutionId, uint32_t testCase) -> std::filesystem::path
{
    auto path = std::filesystem::current_path();
    path /= dataFolder;
    path /= SolutionIdToString(solutionId);
    path += std::to_string(testCase);
    path += dataFileEnding;

    if (std::filesystem::exists(path))
	{
	    return path;
    }

    // Just throw an exception if we're trying to get a nonexisting file
    const auto errc = std::make_error_code(std::errc::no_such_file_or_directory);
    throw std::filesystem::filesystem_error("File not found: ", path, errc);
}

auto
DataBroker::getDataFromFile(const std::filesystem::path& filePath) -> std::string
{
    std::string data;
    std::ifstream fileStream(filePath);
    std::error_code errc;
    const auto fileSize = std::filesystem::file_size(filePath, errc);
    if (errc)
	{
	    std::cout << filePath << " : " << errc.message() << std::endl;
    } else
	{
	    data.reserve(fileSize);
	}

    if (fileStream.is_open())
	{
	    data.assign((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
    }

    fileStream.close();
    return data;
}

} // namespace utils
