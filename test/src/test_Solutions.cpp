// GTest
#include "Definitions.hpp"

#include <gtest/gtest-message.h>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <gtest/internal/gtest-param-util.h>

// Internal
#include <RunSolution.hpp>
#include <Utils.hpp>

// Std
#include <array>
#include <cstdint>
#include <sstream>

namespace SolutionTests {

constexpr ulong numTests = 23;

struct TestParams
{
	utils::SolutionId solutionId{};
	uint32_t testCase{};
	const char* const expectedResult{};
	const char* name{};

	friend auto
	operator<<(std::ostream& outStream, const TestParams& params) -> std::ostream&
	{
	    return outStream << "{SolutionId: " << utils::SolutionIdToString(params.solutionId)
			     << ", testCase: " << params.testCase << ", expected result: " << params.expectedResult
			     << "}";
	}
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
	    const auto solutionDataId = utils::SelectSolutionData(m_solutionId);
	    m_data = utils::DataBroker::getSolutionTestData(solutionDataId, m_testCase);
	}

	utils::SolutionId m_solutionId; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
	uint32_t m_testCase;            // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
	std::string m_data;             // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
	std::string m_expectedResult;   // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)

	struct
	{
		std::string resultValue;
		bool success = false;
	} m_result{}; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
};

TEST_P(SolutionTestFixture, TestSolution) // NOLINT
{
    m_result.resultValue = Solutions::runSolution<true>(m_solutionId, m_data, m_result.success);

    ASSERT_TRUE(m_result.success);
    ASSERT_EQ(m_result.resultValue, m_expectedResult);
}

const std::array<TestParams, numTests> testParameters = {
  TestParams{.solutionId = utils::SolutionId::FattestElfCalories,
	     .testCase = 0,
	     .expectedResult = "24000",
	     .name = utils::SolutionIdToString(utils::SolutionId::FattestElfCalories)},

  TestParams{.solutionId = utils::SolutionId::TopThreeFattestElfCalories,
	     .testCase = 0,
	     .expectedResult = "45000",
	     .name = utils::SolutionIdToString(utils::SolutionId::TopThreeFattestElfCalories)},

  TestParams{.solutionId = utils::SolutionId::RockPaperScissors,
	     .testCase = 0,
	     .expectedResult = "15",
	     .name = utils::SolutionIdToString(utils::SolutionId::RockPaperScissors)},

  TestParams{.solutionId = utils::SolutionId::DecryptedRockPaperScissors,
	     .testCase = 0,
	     .expectedResult = "12",
	     .name = utils::SolutionIdToString(utils::SolutionId::DecryptedRockPaperScissors)},

  TestParams{.solutionId = utils::SolutionId::RucksackReorganization,
	     .testCase = 0,
	     .expectedResult = "157",
	     .name = utils::SolutionIdToString(utils::SolutionId::RucksackReorganization)},

  TestParams{.solutionId = utils::SolutionId::RucksackBadges,
	     .testCase = 0,
	     .expectedResult = "70",
	     .name = utils::SolutionIdToString(utils::SolutionId::RucksackBadges)},

  TestParams{.solutionId = utils::SolutionId::CampCleanup,
	     .testCase = 0,
	     .expectedResult = "2",
	     .name = utils::SolutionIdToString(utils::SolutionId::CampCleanup)},

  TestParams{.solutionId = utils::SolutionId::PartialCampCleanup,
	     .testCase = 0,
	     .expectedResult = "4",
	     .name = utils::SolutionIdToString(utils::SolutionId::PartialCampCleanup)},

  TestParams{.solutionId = utils::SolutionId::RearrangeSupplyStacks,
	     .testCase = 0,
	     .expectedResult = "CMZ",
	     .name = utils::SolutionIdToString(utils::SolutionId::RearrangeSupplyStacks)},

  TestParams{.solutionId = utils::SolutionId::RearrangeSupplyStacksWithAdvancedCrane,
	     .testCase = 0,
	     .expectedResult = "MCD",
	     .name = utils::SolutionIdToString(utils::SolutionId::RearrangeSupplyStacksWithAdvancedCrane)},

  TestParams{.solutionId = utils::SolutionId::TuningTrouble,
	     .testCase = 0,
	     .expectedResult = "7",
	     .name = utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::TuningTrouble,
	     .testCase = 1,
	     .expectedResult = "5",
	     .name = utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::TuningTrouble,
	     .testCase = 2,
	     .expectedResult = "6",
	     .name = utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::TuningTrouble,
	     .testCase = 3,
	     .expectedResult = "10",
	     .name = utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::TuningTrouble,
	     .testCase = 4,
	     .expectedResult = "11",
	     .name = utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::MessageTuningTrouble,
	     .testCase = 0,
	     .expectedResult = "19",
	     .name = utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::MessageTuningTrouble,
	     .testCase = 1,
	     .expectedResult = "23",
	     .name = utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::MessageTuningTrouble,
	     .testCase = 2,
	     .expectedResult = "23",
	     .name = utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::MessageTuningTrouble,
	     .testCase = 3,
	     .expectedResult = "29",
	     .name = utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::MessageTuningTrouble,
	     .testCase = 4,
	     .expectedResult = "26",
	     .name = utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{.solutionId = utils::SolutionId::NoSpace,
	     .testCase = 0,
	     .expectedResult = "95437",
	     .name = utils::SolutionIdToString(utils::SolutionId::NoSpace)},

  TestParams{.solutionId = utils::SolutionId::YesSpace,
	     .testCase = 0,
	     .expectedResult = "24933642",
	     .name = utils::SolutionIdToString(utils::SolutionId::YesSpace)},

  TestParams{.solutionId = utils::SolutionId::TreetopTreeHouse,
	     .testCase = 0,
	     .expectedResult = "21",
	     .name = utils::SolutionIdToString(utils::SolutionId::TreetopTreeHouse)},
};

INSTANTIATE_TEST_SUITE_P( // NOLINT
  AoC2022, SolutionTestFixture, testing::ValuesIn(testParameters),
  [](const testing::TestParamInfo<SolutionTestFixture::ParamType>& info)
  { return std::string(info.param.name) + "_" + std::to_string(info.index); });

} // namespace SolutionTests

// NOLINTBEGIN
auto
main(int argc, char** argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// NOLINTEND