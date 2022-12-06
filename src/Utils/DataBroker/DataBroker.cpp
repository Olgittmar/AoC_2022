#include "DataBroker.hpp"

#include <Definitions.hpp>
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
DataBroker::getSolutionTestData(SolutionId solutionId, int testCase) -> std::string
{
    const auto filePath = getTestDataFileFullPath(solutionId, testCase);
    return getDataFromFile(filePath);
}

auto
DataBroker::getDataFileFullPath(SolutionId solutionId) -> std::filesystem::path
{
    auto path = std::filesystem::current_path();
    path /= dataFolder;
    path /= SolutionIdToString(solutionId);
    path += dataFileEnding;

    if (std::filesystem::exists(path)) {
	    return path;
    }

    // Just throw an exception if we're trying to get a nonexisting file
    const auto errc = std::make_error_code(std::errc::no_such_file_or_directory);
    throw std::filesystem::filesystem_error("File not found: ", path, errc);
}

auto
DataBroker::getTestDataFileFullPath(SolutionId solutionId, int testCase) -> std::filesystem::path
{
    auto path = std::filesystem::current_path();
    path /= dataFolder;
    path /= SolutionIdToString(solutionId);
    path += std::to_string(testCase);
    path += dataFileEnding;

    if (std::filesystem::exists(path)) {
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
    if (errc) {
	    std::cout << filePath << " : " << errc.message() << std::endl;
    } else {
	    data.reserve(fileSize);
	}

    if (fileStream.is_open()) {
	    data.assign((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
    }

    fileStream.close();
    return data;
}

} // namespace utils
