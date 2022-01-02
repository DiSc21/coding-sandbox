#include <gtest/gtest.h>
#include <iostream>

TEST(test_case, simple_test)
{
    EXPECT_EQ(2,2);
    std::cout << "TEST test" << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

