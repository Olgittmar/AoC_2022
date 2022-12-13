// GTest
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <gtest/internal/gtest-param-util.h>

// Internal
#include <ElfCalories.hpp>
#include <RunSolution.hpp>
#include <Utils.hpp>

// Std
#include <array>
#include <cstdint>
#include <sstream>

namespace SolutionTests {
struct TestParams
{
	utils::SolutionId solutionId{};
	uint32_t testCase{};
	uint32_t expectedResult{};
	const char* name{};
};

class SolutionTestFixture : public ::testing::TestWithParam<TestParams>
{
    protected:

	SolutionTestFixture()
	{
	    const auto params = GetParam();
	    m_solutionId = params.solutionId;
	    m_testCase = params.testCase;
	    m_expectedResult = params.expectedResult;
	}

	void
	SetUp() override
	{
	    std::cout << "Fetching test data..." << std::endl;
	    const auto solutionDataId = utils::SelectSolutionData(m_solutionId);
	    m_data = utils::DataBroker::getSolutionTestData(solutionDataId, m_testCase);
	    std::cout << "Got test data." << std::endl;
	}

	utils::SolutionId m_solutionId; // NOLINT
	uint32_t m_testCase;            // NOLINT
	std::string m_data;             // NOLINT
	uint32_t m_expectedResult;      // NOLINT

	struct
	{
		std::uint32_t resultValue = 0;
		bool success = false;
	} m_result{}; // NOLINT
};

TEST_P(SolutionTestFixture, TestSolution) // NOLINT
{
    m_result.resultValue = Solutions::runSolution(m_solutionId, m_data, m_result.success);

    ASSERT_TRUE(m_result.success);
    ASSERT_EQ(m_result.resultValue, m_expectedResult);
}

const std::array<TestParams, 4> testParameters = {
  TestParams{.solutionId = utils::SolutionId::FattestElfCalories,
	     .testCase = 0,
	     .expectedResult = 24000,
	     .name = utils::SolutionIdToString(utils::SolutionId::FattestElfCalories)},

  TestParams{.solutionId = utils::SolutionId::TopThreeFattestElfCalories,
	     .testCase = 0,
	     .expectedResult = 45000,
	     .name = utils::SolutionIdToString(utils::SolutionId::TopThreeFattestElfCalories)},

  TestParams{.solutionId = utils::SolutionId::RockPaperScissors,
	     .testCase = 0,
	     .expectedResult = 15,
	     .name = utils::SolutionIdToString(utils::SolutionId::RockPaperScissors)},

  TestParams{.solutionId = utils::SolutionId::DecryptedRockPaperScissors,
	     .testCase = 0,
	     .expectedResult = 12,
	     .name = utils::SolutionIdToString(utils::SolutionId::DecryptedRockPaperScissors)},
};

INSTANTIATE_TEST_SUITE_P( // NOLINT
  AoC2022, SolutionTestFixture, testing::ValuesIn(testParameters),
  [](const testing::TestParamInfo<SolutionTestFixture::ParamType>& info) { return info.param.name; });

} // namespace SolutionTests

// NOLINTBEGIN
auto
main(int argc, char** argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// NOLINTEND