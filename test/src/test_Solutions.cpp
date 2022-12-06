// NOLINTBEGIN
#include "DataBroker/DataBroker.hpp"
#include "RockPaperScissors.hpp"

#include <gtest/gtest.h>
// NOLINTEND
#include <ElfCalories.hpp>
#include <sstream>

TEST(SolutionsTest, ElfCalories_0) // NOLINT
{
    std::cout << "In Solutions_test.ElfCalories_0" << std::endl;
    constexpr uint32_t expectedReslut = 24000;

    std::cout << "Fetching test data..." << std::endl;
    const auto data = utils::DataBroker::getSolutionTestData(utils::SolutionId::FattestElfCalories, 0);
    std::cout << "Got test data." << std::endl;

    bool success = false;

    std::cout << "Getting calories of elf with highest calories count..." << std::endl;
    const auto result = Solutions::GetCaloriesOfElfWithMostCalories(data, success);
    std::cout << "Got " << result << " calories." << std::endl;

    ASSERT_TRUE(success);
    ASSERT_EQ(result, expectedReslut);
}

TEST(SolutionsTest, TopThreeElfCalories_0) // NOLINT
{
    std::cout << "In Solutions_test.TopThreeElfCalories_0" << std::endl;
    constexpr uint32_t expectedResult = 45000;

    std::cout << "Fetching test data..." << std::endl;
    const auto data = utils::DataBroker::getSolutionTestData(utils::SolutionId::TopThreeFattestElfCalories, 0);
    std::cout << "Got test data." << std::endl;

    bool success = false;

    std::cout << "Getting calories of top 3 elves with highest calories count..." << std::endl;
    const auto result = Solutions::GetCaloriesOfTopThreeElvesWithMostCalories(data, success);
    std::cout << "Got " << result << " calories." << std::endl;

    ASSERT_TRUE(success);
    ASSERT_EQ(result, expectedResult);
}

TEST(SolutionsTest, RockPaperScissorsStrategyGuideScore_0) // NOLINT
{
    std::cout << "In Solutions_test.RockPaperScissorsStrategyGuideScore_0" << std::endl;
    constexpr uint32_t expectedResult = 15;

    std::cout << "Fetching test data..." << std::endl;
    const auto data = utils::DataBroker::getSolutionTestData(utils::SolutionId::RockPaperScissors, 0);
    std::cout << "Got test data." << std::endl;

    bool success = false;

    std::cout << "Getting calories of top 3 elves with highest calories count..." << std::endl;
    const auto result = Solutions::GetScoreOfStrategyGuide(data, success);
    std::cout << "Got " << result << " calories." << std::endl;

    ASSERT_TRUE(success);
    ASSERT_EQ(result, expectedResult);
}

// NOLINTBEGIN
auto
main(int argc, char** argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// NOLINTEND