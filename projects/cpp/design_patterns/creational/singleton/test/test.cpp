#include <gtest/gtest.h>
#include <iostream>

#include "../src/DS_Singleton.hpp"

class TestCount
{
  public:
    int getSingletonCount(){
        auto singleton = DS_Singleton::getInstance();
        return singleton->getCount();
    }
};


TEST(test_case, simple_test0)
{
    auto singleton = DS_Singleton::getInstance();
    EXPECT_EQ(0, singleton->getCount());
}

TEST(test_case, simple_test1)
{
    TestCount test_count;
    EXPECT_EQ(1, test_count.getSingletonCount());
}

TEST(test_case, simple_test2)
{
    auto singleton = DS_Singleton::getInstance();
    EXPECT_EQ(2, singleton->getCount());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

