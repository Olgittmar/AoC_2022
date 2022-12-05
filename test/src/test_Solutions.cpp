// NOLINTBEGIN
#include "DataBroker/DataBroker.hpp"

#include <gtest/gtest.h>
// NOLINTEND
#include <ElfCalories.hpp>
#include <sstream>

TEST(Solutions_test, ElfCalories_0) // NOLINT
{
    constexpr uint32_t expectedReslut = 24000;
    const auto data = utils::DataBroker::getSolutionTestData(utils::SolutionId::FattestElfCalories, 0);
    bool success = false;
    const auto result = Solutions::GetCaloriesOfElfWithMostCalories(data, success);

    ASSERT_TRUE(success);
    ASSERT_EQ(result, expectedReslut);
}

// NOLINTBEGIN
auto
main(int argc, char** argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// NOLINTEND