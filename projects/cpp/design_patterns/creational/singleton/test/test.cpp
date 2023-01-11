#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_Singleton.hpp"

/// @brief simple test class
class TestCount
{
  public:
    /// @brief simple testfunction calling getInstance and returning instance count
    /// @return get the count number
    [[nodiscard]] static auto getSingletonCount() -> int
    {
        auto singleton = DS_Singleton::getInstance();
        return singleton->getCount();
    }
};


TEST(test_case, simple_test0) // NOLINT
{
    auto singleton = DS_Singleton::getInstance();
    EXPECT_EQ(0, singleton->getCount());
}


TEST(test_case, simple_test1) // NOLINT
{
    TestCount test_count;
    EXPECT_EQ(1, test_count.getSingletonCount());
}


TEST(test_case, simple_test2) // NOLINT
{
    auto singleton = DS_Singleton::getInstance();
    EXPECT_EQ(2, singleton->getCount());
}


int main(int argc, char **argv) // NOLINT
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
