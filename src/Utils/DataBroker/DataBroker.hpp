#ifndef DATABROKER_HPP
#define DATABROKER_HPP

#include <Definitions.hpp>
#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace utils {

class DataBroker
{
    public:

	static auto getSolutionData(SolutionId solutionId) -> std::string;
	static auto getSolutionTestData(SolutionId solutionId, uint32_t testCase) -> std::string;

    private:

	static auto getDataFileFullPath(SolutionId solutionId) -> std::filesystem::path;
	static auto getTestDataFileFullPath(SolutionId solutionId, uint32_t testCase) -> std::filesystem::path;
	static auto getDataFromFile(const std::filesystem::path& filePath) -> std::string;
};

} // namespace utils

#endif