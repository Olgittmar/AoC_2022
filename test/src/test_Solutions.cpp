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

constexpr ulong numTests = 27;

struct TestParams
{
	constexpr TestParams(utils::SolutionId solutionIdInit, uint32_t testCaseInit, const char* expectedResultInit,
			     const char* nameInit)
	  : solutionId(solutionIdInit), testCase(testCaseInit), expectedResult(expectedResultInit), name(nameInit)
	{
	}

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

constexpr std::array<TestParams, numTests> testParameters = {
  TestParams{utils::SolutionId::FattestElfCalories, 0, "24000",
	     utils::SolutionIdToString(utils::SolutionId::FattestElfCalories)},

  TestParams{utils::SolutionId::TopThreeFattestElfCalories, 0, "45000",
	     utils::SolutionIdToString(utils::SolutionId::TopThreeFattestElfCalories)},

  TestParams{utils::SolutionId::RockPaperScissors, 0, "15",
	     utils::SolutionIdToString(utils::SolutionId::RockPaperScissors)},

  TestParams{utils::SolutionId::DecryptedRockPaperScissors, 0, "12",
	     utils::SolutionIdToString(utils::SolutionId::DecryptedRockPaperScissors)},

  TestParams{utils::SolutionId::RucksackReorganization, 0, "157",
	     utils::SolutionIdToString(utils::SolutionId::RucksackReorganization)},

  TestParams{utils::SolutionId::RucksackBadges, 0, "70", utils::SolutionIdToString(utils::SolutionId::RucksackBadges)},

  TestParams{utils::SolutionId::CampCleanup, 0, "2", utils::SolutionIdToString(utils::SolutionId::CampCleanup)},

  TestParams{utils::SolutionId::PartialCampCleanup, 0, "4",
	     utils::SolutionIdToString(utils::SolutionId::PartialCampCleanup)},

  TestParams{utils::SolutionId::RearrangeSupplyStacks, 0, "CMZ",
	     utils::SolutionIdToString(utils::SolutionId::RearrangeSupplyStacks)},

  TestParams{utils::SolutionId::RearrangeSupplyStacksWithAdvancedCrane, 0, "MCD",
	     utils::SolutionIdToString(utils::SolutionId::RearrangeSupplyStacksWithAdvancedCrane)},

  TestParams{utils::SolutionId::TuningTrouble, 0, "7", utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{utils::SolutionId::TuningTrouble, 1, "5", utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{utils::SolutionId::TuningTrouble, 2, "6", utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{utils::SolutionId::TuningTrouble, 3, "10", utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{utils::SolutionId::TuningTrouble, 4, "11", utils::SolutionIdToString(utils::SolutionId::TuningTrouble)},

  TestParams{utils::SolutionId::MessageTuningTrouble, 0, "19",
	     utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{utils::SolutionId::MessageTuningTrouble, 1, "23",
	     utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{utils::SolutionId::MessageTuningTrouble, 2, "23",
	     utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{utils::SolutionId::MessageTuningTrouble, 3, "29",
	     utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{utils::SolutionId::MessageTuningTrouble, 4, "26",
	     utils::SolutionIdToString(utils::SolutionId::MessageTuningTrouble)},

  TestParams{utils::SolutionId::NoSpace, 0, "95437", utils::SolutionIdToString(utils::SolutionId::NoSpace)},

  TestParams{utils::SolutionId::YesSpace, 0, "24933642", utils::SolutionIdToString(utils::SolutionId::YesSpace)},

  TestParams{utils::SolutionId::TreetopTreeHouse, 0, "21",
	     utils::SolutionIdToString(utils::SolutionId::TreetopTreeHouse)},

  TestParams{utils::SolutionId::TreetopTreeHouseDist, 0, "8",
	     utils::SolutionIdToString(utils::SolutionId::TreetopTreeHouseDist)},

  TestParams{utils::SolutionId::RopeBridge, 0, "13", utils::SolutionIdToString(utils::SolutionId::RopeBridge)},

  TestParams{utils::SolutionId::RopeBridgeWithLongRopes, 0, "1",
	     utils::SolutionIdToString(utils::SolutionId::RopeBridgeWithLongRopes)},

  TestParams{utils::SolutionId::RopeBridgeWithLongRopes, 1, "36",
	     utils::SolutionIdToString(utils::SolutionId::RopeBridgeWithLongRopes)},
};

class SolutionTestFixture : public ::testing::TestWithParam<TestParams>
{
    public:

	SolutionTestFixture() = default;

	void
	SetUp() override
	{
	    const auto params = testing::TestWithParam<TestParams>::GetParam();
	    const auto solutionDataId = utils::SelectSolutionData(params.solutionId);
	    m_data = utils::DataBroker::getSolutionTestData(solutionDataId, params.testCase);
	}

	std::string m_data; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
};

auto
TestNameGenerator(const testing::TestParamInfo<SolutionTestFixture::ParamType>& info) -> std::string
{
    auto testName = std::string{"SolutionsTest"} + info.param.name + std::to_string(info.index);
    return testName;
}

TEST_P(SolutionTestFixture, TestSolution) // NOLINT
{
    const auto params = testing::TestWithParam<TestParams>::GetParam();
    bool success = false;
    const std::string expectedResult{params.expectedResult};

    const auto result = Solutions::runSolution<true>(params.solutionId, m_data, success);

    ASSERT_TRUE(success);
    ASSERT_EQ(result, expectedResult);
}

INSTANTIATE_TEST_SUITE_P(AoC_2022, SolutionTestFixture, testing::ValuesIn(testParameters), TestNameGenerator); // NOLINT

} // namespace SolutionTests

// NOLINTBEGIN
auto
main(int argc, char** argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// NOLINTEND