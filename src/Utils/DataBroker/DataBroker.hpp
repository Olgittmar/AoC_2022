#ifndef UTILS_DATABROKER_DATABROKER_HPP
#define UTILS_DATABROKER_DATABROKER_HPP

#include <Definitions.hpp>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <map>
#include <string>
#include <unordered_map>

namespace utils {

class DataBroker
{
    public:

	static auto getSolutionData(SolutionId solutionId) -> std::string;
	static auto getSolutionTestData(SolutionId solutionId, uint32_t testCase) -> std::string;
	static auto getSolutionBenchmarkDataGenerator(SolutionId solutionId) -> std::function<std::string()>;

    private:

	static auto getDataFileFullPath(SolutionId solutionId) -> std::filesystem::path;
	static auto getTestDataFileFullPath(SolutionId solutionId, uint32_t testCase) -> std::filesystem::path;
	static auto getDataFromFile(const std::filesystem::path& filePath) -> std::string;
};

} // namespace utils

#endif