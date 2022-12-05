// NOLINTBEGIN
#include <gtest/gtest.h>
// NOLINTEND
#include <Hello.hpp>
#include <sstream>

TEST(Hello_test, hello) // NOLINT
{
    std::stringstream ss;
    Hello::PrintHelloWorld(ss);
    EXPECT_EQ("Hello world!\n", ss.str()); // NOLINT
}

// NOLINTBEGIN
auto
main(int argc, char** argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// NOLINTEND